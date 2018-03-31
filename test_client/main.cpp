#include <QCoreApplication>
#include "ServiceBus.h"
#include "DmsTopoData_m.h"
int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    ServiceBus srv_client(AP_DMS_SCADA,17779);

    TRequestDmsTopo req;
    req.req_id = 99;
    long id = 117375065305120943;
    req.vec_key.push_back(id);

    char* buf;
    int len = 0;
    M_CODE(req,buf,len);
    printf("mcode len = %d\n",len);
    srv_client.RequestSync(1,0,buf,len);
    delete []buf;

    //115967690404790274

    //return a.exec();
}
