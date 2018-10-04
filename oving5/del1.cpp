#include <utility>

#include <fstream>
#include <vector>
#include <iostream>
#include <memory>

std::vector<std::string> NAMES = {"Almås Annabelle Solem", "Andersson William", "Andersson Vegard", "Andresen Sebastian Martin", "Aune Jostein Johansen", "Axell Christian", "Daniel Larsen",
                       "Bakhmadov Magomed Khatujevitsj", "Braathen Mathias", "Bui Aria Thuy Dung", "Bø Halvor Fladsrud", "Christiansen Herman", "Dahl Magnus", "Dalseth Christian Mathias", "Debik Karol Jerzy",
                       "Elvemo Sebastian Aanesland", "Fossland Ole-Henrik", "Frantzen Odd-Erik", "Fridheim Marius", "Fylling Johan-Henrik", "Garmann Ingelin", "Gram Hans-Jeiger", "Habeeb Khaled Mohammad",
                       "Halvarsson Kevin Mentzoni", "Haugum Terje", "Helgeland Kevin Andre", "Hestnes Håkon Dalen", "Hjelle Sara", "Holt Eyvind Nikolai", "Hynne Sigurd", "Iversen Anders Hallem",
                       "Jacobsen Sigurd Lø¸ite", "Jacobsen William Chakroun", "Johansen Aleksander", "Johansen Kristaver Birkeland", "Johansen Eivind Alfsvåg", "Kampenhå y Kristian", "Knutsen Yair Day",
                       "Knutsen Mathias", "Koteng Markus Thomassen", "Kristoffersen Jonas", "Larsen Knut Johan", "Larsen Albert Ohrem", "Larsson, Øivind Haugerø", "Lervik Eivind Hestnes",
                       "Li Jingyi", "Lilleeng Simon", "Martinsen Magnus Revheim", "Martinsen Herman Ryen", "Mediå Fredrik", "Mellemseter Michael", "Midttun Jonathan", "Moan Martin Andreas", "Monsen Fredrik",
                       "Nicolausson Sander", "Nordseth Morten Nyang", "Nygård Marius", "Nystuen Ådne", "Opsahl Elisabeth Marie", "Paulshus Sindre Haugland", "Rad Saadat Ilia", "Ramberg Håvard Hammer", "Roll Erling",
                       "Rondestvedt Trond Jacob", "Rø stgård Kim Richard", "Sandnes Martin", "Siiri Anette Olli", "Skaug Oscar Tideman Borgerud", "Stavseng Ådne Eide", "Strand Snorre Kristoffer", "Strø mhylden Ben Oscar",
                       "Sundø y Erlend", "Søther Ane", "Sørlie Lars", "Teiler-Johnsen Mari", "Tengs Simen Sølevik", "Thomassen Sindre", "Thorkildsen Patrick", "Timdal Eivind Rui", "Tokvam Balder",
                       "Tran Quan Nguyen", "Tverfjell Julie Isabelle Malmedal", "Ullah Mona", "Valen Ruben Solvang", "Valstadsve Øyvind", "Vatle Jan-Marius", "Vedøy Rune", "Vesterlid Ørjan Bostad",
                       "Wangensteen Kim Anners", "Wichstrøm Brage", "Worren Magne", "Østtveit Bjørnar", "Øverland Sveinung", "Øvsthus Vebjørn Hansen", "Ådnanes Stian", "Aasvestad Jørgen"};

class HashTable{
public:
    unsigned long hash(const std::string & string){
        unsigned long val = 0;
        for(int i = 0; i < string.size(); i++){
            val += ((char)string[i] << i) + (char)string[i];
        }
        return val%elements.size();
    }

    HashTable setCapacity(unsigned long i){
        elements.reserve(static_cast<unsigned long>(i / idealLoad));
        while (elements.size()<elements.capacity()){
            elements.push_back(nullptr);
        }
        return *this;
    }
    void add(const std::string &key){
        _size++;
        unsigned long hashed = hash(key);
        if (not elements[hashed])
            elements[hashed] = std::make_shared<Node>(key);
        else {
            elements[hash(key)]->add(key);
            kollisjoner++;
        }
    }
    std::string get(const std::string &key){
        return elements[hash(key)]->get(key);
    }
    double load(){
        return double(_size) / elements.capacity();
    }

    int kollisjoner = 0;

private:
    class Node{
    public:
        explicit Node(std::string ikey) : key(std::move(ikey)){};
        void add(std::string ikey){
            if(next){
                next->add(ikey);
            }else{
                std::cout << "add: " << key << " og " << ikey << std::endl;
                next = std::make_shared<Node>(Node(ikey));
            }
        }
        std::string get(std::string ikey){
            if (ikey==key){
                return key;
            }else{
                std::cout << "get: " << key << " og " << ikey << std::endl;
                return next->get(ikey);
            }
        }

    private:
        std::string key;
        std::shared_ptr<Node> next = nullptr;
    };
    unsigned long _size = 0;
    float idealLoad = 0.8;
    std::vector<std::shared_ptr<Node>> elements;
};
int main() {
    HashTable table = HashTable()
            .setCapacity(NAMES.size());
    for( const std::string &name : NAMES ){
        table.add(name);
    }

    for( const std::string &name : NAMES ){
        table.get(name);
    }

    std::cout << "load faktor: " << table.load() << std::endl;
    std::cout << "kollisjoner: " << table.kollisjoner << std::endl;


}