#ifndef CDMSTOPOSERVICE_H
#define CDMSTOPOSERVICE_H

#include "ITopoService.h"
class CDmsTopoImpl;
class CDmsTopoService : public ITopoService
{
public:
    CDmsTopoService();
    ~CDmsTopoService();
    virtual void doService(char* requestBuffer, int requestlen, char** responseBuffer, int* responselen);
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
