#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
using namespace std;
void Error(const char * why, const int exitCode=1)
{
    cerr<<why<<endl;
    exit(exitCode);
}
int main()
{

    sockaddr_in * self_addr = new (sockaddr_in);
    self_addr->sin_family = AF_INET;
    self_addr->sin_port = 0;
    self_addr->sin_addr.s_addr = 0;
    char * buf= new char[256];
    sockaddr_in * srv_addr = new (sockaddr_in);
    srv_addr->sin_family = AF_INET;
    srv_addr->sin_port = htons(13);
    srv_addr->sin_addr.s_addr = inet_addr("82.179.90.12");
    int s = socket(AF_INET, SOCK_STREAM, 0); // TCP
    if (s==-1) {
        Error("Error open socket",11);
    }
    int rc = bind(s,(const sockaddr*) self_addr,sizeof(sockaddr_in));
    if (rc==-1) {
        close(s);
        Error("Error bind",12);
    }
    rc = connect(s,(const sockaddr*)srv_addr, sizeof(sockaddr_in));
    if (rc == -1) {
        close(s);
        Error("Error connect",13);
    }
    rc=recv(s,buf,256,0);
    if (rc == -1) {
        close(s);
        Error("Error receive",14);
    }
    buf[rc]='\0';
    cout<<"We receive "<<buf<<endl;
    close(s);
    delete self_addr;
    delete srv_addr;
    delete[] buf;
    return 0;
}
