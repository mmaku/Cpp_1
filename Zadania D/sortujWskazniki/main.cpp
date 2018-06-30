#include <iostream>
#include <assert.h>

auto Sortuj3Wskazniki(std::string* WE[]) -> void
{
    assert(WE[0] && WE[1] && WE[2]);
    if(*WE[1] < *WE[0])
    {
        std::swap(WE[0], WE[1]);
    }

    if(*WE[2] < *WE[1])
    {
        std::swap(WE[1], WE[2]);
    }

    if(*WE[1] < *WE[0])
    {
        std::swap(WE[0], WE[1]);
    }
}

auto test_Sortuj3Wskazniki() -> void;

int main()
{
    test_Sortuj3Wskazniki();
    return 0;
}

auto test_Sortuj3Wskazniki() -> void
{
    std::string napisy[]={"Dabacki","Babacki","Abacki"};
    std::string* wskazniki[]={napisy,napisy+1,napisy+2};

    Sortuj3Wskazniki(wskazniki);

    assert(napisy[0]=="Dabacki");
    assert(napisy[1]=="Babacki");
    assert(napisy[2]=="Abacki");

    assert(*(wskazniki[0])=="Abacki");
    assert(*(wskazniki[1])=="Babacki");
    assert(*(wskazniki[2])=="Dabacki");

    std::cerr << "test_Sortuj3Wskazniki ok\n";
}
