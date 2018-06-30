#include <iostream>
#include <vector>
#include <cassert>

bool CZYsort(const std::vector<std::string>& WE)
{
    bool WY=true;
    if(2 < WE.size())
    {
        for(unsigned int i=0; i < WE.size()-1; i++)
        {
            WY &= WE[i]<WE[i+1];
        }
    }
    else if(WE.size()==2)
    {
        WY = WE[0] < WE[1];
    }
    return WY;
}

void zamianaSTR(std::string& WE1 ,std::string& WE2)
{
    std::string TMP(WE1);
    WE1=WE2;
    WE2=TMP;
}

std::vector<std::string> BUBsort(const std::vector<std::string>& WE)
{
    std::vector<std::string> WY(WE);
    if(!WE.empty())
    {
        while(!CZYsort(WY))
        {
            for(unsigned int i=0; i < WY.size()-1; i++)
            {
                if(WY[i]>WY[i+1])
                {
                    zamianaSTR(WY[i], WY[i+1]);
                }
            }
        }
    }
    return WY;
}

void TEST_BUBsort();

int main()
{
    TEST_BUBsort();
    return 0;
}

void TEST_BUBsort()
{
    std::vector<std::string> dni = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    std::vector<std::string> dniSORT = {"Friday", "Monday", "Saturday", "Sunday", "Thursday", "Tuesday", "Wednesday"};
    std::vector<std::string> dniBUBsort(BUBsort(dni));
    assert(dniBUBsort == dniSORT);

    std::cerr << "Testy OK!\n";
}
