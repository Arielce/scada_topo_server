#ifndef CDMSTOPOSERVICE_H
#define CDMSTOPOSERVICE_H

#include "ITopoService.h"
//class CGraph;
class CDmsTopoImpl;
class CDmsTopoService : public ITopoService
{
public:
    CDmsTopoService();
    ~CDmsTopoService();
    void setGraph(SCADA_ALG::CGraph* g);
    void doService(char* requestBuffer, int requestlen, char** responseBuffer, int* responselen);
private:
    CDmsTopoImpl *m_Impl;
};

class CDmsTopoServiceFactory : public ITopoServiceFactory
{
public:
     void CreateTopoService(ITopoService** p_obj);
     void Release();
};

#endif // CDMSTOPOSERVICE_H
