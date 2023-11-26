#include <vector>
#include <iostream>
#include <map>
#include <iomanip>

class Ebook{
public:
    void Read(int user, int page){
        int page_old = page_by_id_[user];
        if (count_people_reading_page_.size() < page){
            count_people_reading_page_.resize(page);
        }
        for(int i = page_old; i < page; ++i){
            ++count_people_reading_page_[i];
        }
        page_by_id_[user] = page;
    }

    double Cheer(int user) const{
        if(page_by_id_.count(user) == 0){
            return 0.0;
        }
        if (page_by_id_.size() == 1) {
            return 1.0;
        }
        int page = page_by_id_.at(user);
        if (page == 0 ){
            return 0.0;
        }

        int people_count = count_people_reading_page_.at(page - 1) - 1;
        return  1 - 1.0 * people_count / (page_by_id_.size() - 1);
    }
private:
    std::vector < int > count_people_reading_page_;
    std::map<int, int> page_by_id_;

};


int main(){
    Ebook ebook;
    int count_strings = 0;
    std::cin >> count_strings;
    std::cout << std::setprecision(6);
    for (int i = 0; i < count_strings; ++i) {
        std::string req_type;
        std::cin >> req_type;
        if(req_type == "CHEER"){
            int user_id;
            std::cin >> user_id;
            std::cout << ebook.Cheer(user_id) << std::endl;
        }

        if (req_type == "READ"){
            int user_id, page;
            std::cin >> user_id >> page;
            ebook.Read(user_id, page);
        }
    }
}