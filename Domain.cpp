#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <utility>
#include <vector>
#include <cassert>

using namespace std;

class Domain {
    // разработайте класс домена
public:
    // конструктор должен позволять конструирование из string, с сигнатурой определитесь сами
    explicit Domain(string domainStr):
            domain_str_(domainStr.rbegin(),domainStr.rend()){
        domain_str_ += ".";
    }

    // разработайте operator==
    friend bool operator==(const Domain &lhs, const Domain &rhs) {
        return lhs.domain_str_ == rhs.domain_str_;
    }

    bool operator<(const Domain &rhs) const {
        return domain_str_ < rhs.domain_str_;
    }

    const string &GetDomainStr() const {
        return domain_str_;
    }

    // разработайте метод IsSubdomain, принимающий другой домен и возвращающий true, если this его поддомен
    bool IsSubdomain(const Domain& other) const{
        if(domain_str_.size() < other.GetDomainStr().size()){
            return false;
        }
        auto str = domain_str_.substr(0,other.GetDomainStr().size());
        return str ==other.GetDomainStr();
    }
private:
    string domain_str_;
};

class DomainChecker {
public:
    // конструктор должен принимать список запрещённых доменов через пару итераторов
    template <typename InputIt>
    DomainChecker(InputIt begin, InputIt end) : forbidden_domains_(begin, end)
    {
        std::sort(forbidden_domains_.begin(), forbidden_domains_.end());
        auto last = std::unique(forbidden_domains_.begin(), forbidden_domains_.end(),[](const auto& lhs, const auto& rhs){
            return (rhs.IsSubdomain(lhs) || lhs.IsSubdomain(rhs));
        });
        forbidden_domains_.erase(last, forbidden_domains_.end());
    }
    // разработайте метод IsForbidden, возвращающий true, если домен запрещён
    bool IsForbidden(const Domain& domain) const {
        auto it = std::upper_bound(forbidden_domains_.begin(), forbidden_domains_.end(),domain);
        if (it == forbidden_domains_.begin()) return false;
        return (domain.IsSubdomain(*(it-1)));
    }

private:
    vector<Domain> forbidden_domains_;
};

// разработайте функцию ReadDomains, читающую заданное количество доменов из стандартного входа
vector<Domain> ReadDomains(istream& input, size_t count){
    vector<Domain> domains;
    domains.reserve(count);

    for(size_t i = 0; i < count; ++i){
        string domain_str;
        getline (input, domain_str);
        domains.emplace_back(domain_str);
    }
    return domains;
}


template <typename Number>
Number ReadNumberOnLine(istream& input) {
    string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}


void TestDomain() {
    Domain domain1("example.com");
    Domain domain2("example.com");
    Domain domain3("subdomain.example.com");
    Domain domain4("other.com");

    assert(domain1 == domain2);
    assert(domain3.IsSubdomain(domain1));
    assert(!domain1.IsSubdomain(domain4));
}

void TestReadDomains() {
    istringstream input("example.com\nsubdomain.example.com\nother.com\n");
    vector<Domain> domains = ReadDomains(input, 3);

    assert(domains.size() == 3);
    assert(domains[0] == Domain("example.com"));
    assert(domains[1] == Domain("subdomain.example.com"));
    assert(domains[2] == Domain("other.com"));
}

void TestDomainChecker() {
    vector<Domain> forbidden_domains = {Domain("example.com"), Domain("subdomain.example.com")};
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    assert(checker.IsForbidden(Domain("example.com")));
    assert(checker.IsForbidden(Domain("subdomain.example.com")));
    assert(!checker.IsForbidden(Domain("other.com")));
}

int main() {
    TestDomain();
    TestReadDomains();
    TestDomainChecker();
    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}