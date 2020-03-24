#include"mysocket.h"

#define EPOLL_SIZE 50

int main(int argc, char* argv[]){
  int srv_sock, cln_sock;
  struct sockaddr_in srv_adr, cln_adr;
  socklen_t adr_sz;
  int str_len, i;
  char buffer[BUF_SIZE];

  struct epoll_event *ep_events;
  struct epoll_event ep_event;
  int epfd, event_cnt;

  if(argc != 2){
    printf("usage:%s <port>\n",argv[0]);
    exit(1);
  }

  srv_sock = socket(PF_INET, SOCK_STREAM,0);
  if(srv_sock == -1){
    printf("socket() error\n");
    exit(1);
  }

  memset(&srv_adr, 0, sizeof(srv_adr));
  srv_adr.sin_family = AF_INET;
  srv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
  srv_adr.sin_port = htons(atoi(argv[1]));

  if(bind(srv_sock, (struct sockaddr*)&srv_adr, sizeof(srv_adr)) == -1){
    printf("bind() error\n");
    exit(1);
  }
  if(listen(srv_sock, 5) == -1){
    printf("listen() error\n");
    exit(1);
  }


  epfd = epoll_create(EPOOL_SIZE);
  ep_events = malloc(sizeof(struct epoll_event)*EPOLL_SIZE);
  event.events = EPOLLIN;
  event.data.fd = srv_sock;
  epoll_ctl(epfd, EPOLL_CTL_ADD, srv_sock,&event);

  while(1){
    event_cnt = epoll_wait(epfd, ev_events, EPOLL_SIZE, -1);
    if(event_cnt == -1){
      puts("epoll_wait error\n");
      break;
    }

    for(int i = 0;i < event_cnt; i++){
      if(ev_events[1].data.fd == srv_sock){
	adr_sz = sizeof(cln_adr);
	cln_sock = accept(srv_sock, (struct sockaddr*)&cln_adr, &adr_sz);
	event.events = EPOLLIN;
	event.data.fd = cln_sock;
	epoll_ctl(epfd, EPOLL_CTL_ADD, cln_sock, &event);
	printf("client connect...\n");
      }
      else{
	str_len = read(ev_events[i].data.fd, buffer, BUF_SIZE);
	if(str_len == 0){
	  epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
	  close(ev_events[i].data.fd);
	  printf("client close...\n");
	}
	else{
	  write(ev_events[i].data.fd, buffer, str_len);
	}
      }
    }

    close(srv_sock);
    close(epfd);
    exit(0);  
}
