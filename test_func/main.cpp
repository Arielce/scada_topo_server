#include <QCoreApplication>
#include "CPropertyReader.h"
#include "CConfigurationInfo.h"
#include <string>
using namespace std;
int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    SCADA_ALG::CPropertyReader::loadConfigure("/home/d5000/yanshi/conf/topo_model_rtdb.xml");
    int ret = SCADA_ALG::CPropertyReader::getAllPropertyInfo(SCADA_ALG::CConfigurationInfo::getInst()->getAllProperty());

    SCADA_ALG::IPropertyInfo::AppPropertyInfoMap p = SCADA_ALG::CConfigurationInfo::getInst()->getAllProperty();
    SCADA_ALG::IPropertyInfo::AppPropertyInfoMapIterator it;
    for ( it=p.begin() ;it!=p.end();it++)
    {
        printf("APP=%s\n",it->first.c_str());
        SCADA_ALG::IPropertyInfo::ObjPropertyInfoMapIterator oit;
        for (oit = it->second.begin();oit!=it->second.end();oit++)
        {
            printf("    OBJ=%s \n",oit->first.c_str());

            SCADA_ALG::IPropertyInfo::PropertyInfoMapIterator pit;
            for(pit=oit->second.begin();pit!=oit->second.end();pit++)
            {
                printf("        Property name is %s \n",pit->first.c_str());
                map<string,string>::const_iterator it_map;
                for (it_map=pit->second->begin();it_map != pit->second->end(); it_map++)
                {
                		printf("				k=%s,v=%s\n",it_map->first.c_str(),it_map->second.c_str());
                }
                if (pit->first=="tab_no")
                {
                		SCADA_ALG::CPropertyInfo* cp = dynamic_cast<SCADA_ALG::CPropertyInfo*>(pit->second);
                		printf("tab no is %d \n",cp->tabNo());
                }
            }
        }
    }

    //return a.exec();
}
