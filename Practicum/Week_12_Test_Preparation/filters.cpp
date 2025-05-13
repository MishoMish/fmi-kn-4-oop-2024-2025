#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <functional>
#include <type_traits>

using std::cin, std::cout;

enum class FilterCategoryType
{
    NumericFilter,
    StringFilter,
    LogicalFilter,
    PredefinedFilter
};

enum class FilterType
{
    IntervalFilter,
    EvenFilter,
    DivisibleFilter
};



template<typename T>
class Filter {
public:
    virtual bool matches(const T& item) const = 0;
    virtual std::string getFilterName() const = 0;
    virtual FilterCategoryType getFilterType() const = 0;
    virtual void printDescription(std::ostream& out) const = 0;
    Filter<T>* operator&&(const Filter<T>& other) const;
    Filter<T>* operator||(const Filter<T>& other) const;
    virtual ~Filter() = default;
};

template<typename T>
class NumericFilter : public Filter<T> {
    // static_assert(std::is_arithmetic<T>::value)
public:
    FilterCategoryType getFilterType() const override
    {
        return FilterCategoryType::NumericFilter;
    }
};

template<typename T>
class IntervalFilter : public NumericFilter<T> {
    T _lo;
    T _hi;
public:
    IntervalFilter(T lo, T hi): _lo(lo), _hi(hi) {};
    bool matches(const T& item) const override
    {
        return item >= _lo && item <= _hi;
    }
    std::string getFilterName() const override
    {
        return "IntervalFilter";
    }
    void printDescription(std::ostream& out) const override
    {
        out << "IntervalFilter: [" << _lo << ", " << _hi << "]";
    }
};

template<typename T>
class EvenFilter : public NumericFilter<T>{
public:
    EvenFilter(){};
    bool matches(const T& item)const override
    {
        return item % 2 == 0;
    }
    std::string getFilterName() const override
    {
        return "EvenFilter";
    }   
    void printDescription(std::ostream& out) const override
    {
        out << "EvenFilter: even numbers";
    }
};

template<typename T>
class DivisibleFilter : public NumericFilter<T> {
    T _divisor;
public:

    DivisibleFilter(T divisor): _divisor(divisor){};
    bool matches(const T& item) const override{
        return item % _divisor == 0;
    }
    std::string getFilterName() const override
    {
        return "DivisibleFilter";
    }
    void printDescription(std::ostream& out) const override
    {
        out << "DivisibleFilter: divisible by " << _divisor;
    }
};
/// -------------------------

class StringFilter : public Filter<std::string> {

public:
    FilterCategoryType getFilterType() const override
    {
        return FilterCategoryType::StringFilter;
    }
};

class UpperFilter : public StringFilter {
public:
    UpperFilter(){};
    bool matches(const std::string& s) const override
    {
        for(char c : s) {
            if ( c < 'A' || c > 'Z') {
                return false;
            }
        }
        return true;
    }
    std::string getFilterName() const override
    {
        return "UpperFilter";
    }
    void printDescription(std::ostream& out) const override
    {
        out << "UpperFilter: only uppercase letters";   
    }
};

class LowerFilter : public StringFilter {
public:
    LowerFilter(){};
    bool matches(const std::string& s) const override
    {
        for(char c : s) {
            if ( c < 'A' || c > 'Z') {
                return false;
            }
        }
        return true;
    }
    std::string getFilterName() const override
    {
        return "LowerFilter";
    }
    void printDescription(std::ostream& out) const override
    {
        out << "LowerFilter: only lowercase letters";   
    }
};

class LettersFilter : public StringFilter {
    std::string _allowed;
public:
    LettersFilter(const std::string& allowed):_allowed(allowed){};
    bool matches(const std::string& s) const override
    {
        for(char c : s) {
            bool found = false;
            for(char a : _allowed) {
                if (c == a) {
                    found = true;
                    break;
                }
            }
            if(found == false) {
                return false;
            }
        }
        return true;
    }
    std::string getFilterName() const override
    {
        return "LettersFilter";
    }
    void printDescription(std::ostream& out) const override
    {
        out << "LettersFilter: only letters from " << _allowed;
    }
};

//-----------------------------------------

template<typename T>
class PredefinedFilter : public Filter<T> {
public:
    FilterCategoryType getFilterType() const override
    {
        return FilterCategoryType::PredefinedFilter;
    };
};

template<typename T>
class PredicateFilter : public PredefinedFilter<T> {
    std::function<bool(const T&)> _predicate;
public:
    PredicateFilter(std::function<bool(const T&)> pred): _predicate(pred) {};
    bool matches(const T& item) const override
    {
        return _predicate(item);
    }
    std::string getFilterName() const override
    {
        return "PredicateFilter";
    }
    void printDescription(std::ostream& out) const override
    {
        out << "PredicateFilter: custom predicate";
    }
};

template<typename T>
class BlackListFilter : public PredefinedFilter<T> {
    std::vector<T> _forbidden;
public:
    BlackListFilter(const std::vector<T>& forbidden): _forbidden(forbidden) {};
    bool matches(const T& item) const override
    {
        for(const T& f : _forbidden) {
            if (item == f) {
                return false;
            }
        }
        return true;
    }
    std::string getFilterName() const override
    {
        return "BlackListFilter";
    }
    void printDescription(std::ostream& out) const override
    {
        out << "BlackListFilter: forbidden items";
    }
};

template<typename T>
class WhiteListFilter : public PredefinedFilter<T> {
    std::vector<T> _allowed;
public:
    WhiteListFilter(const std::vector<T>& allowed):_allowed(allowed) {};
    bool matches(const T& item) const override
    {
        for(const T& f : _allowed) {
            if (item == f) {
                return true;
            }
        }
        return false;
    }
    std::string getFilterName() const override
    {
        return "WhiteListFilter";
    };
    void printDescription(std::ostream& out) const override
    {
        out << "WhiteListFilter: allowed items";
    }
};

//---------------------------------

template<typename T>
class LogicalFilter : public Filter<T> {
public:
    LogicalFilter() {};
    LogicalFilter(const std::vector<Filter<T>*>& filters)
    {
        addFilters(filters);
    };
    //to be done
    LogicalFilter(const Filter<T>& filter) = delete;
    LogicalFilter& operator=(const LogicalFilter& other) = delete;

    void addFilters(const std::vector<Filter<T>*> filters) 
    {
        // for(Filter<T>* filter : filters) {
        //     _filters.push_back(filter->clone());
        // }
    }
    FilterCategoryType getFilterType() const override 
    { 
        return FilterCategoryType::LogicalFilter;
    }
    ~LogicalFilter() {
        for(Filter<T>* filter : _filters) {
            delete filter;
        }
    }
protected:
    std::vector<Filter<T>*> _filters;
};

template<typename T>
class AndFilter : public LogicalFilter<T> {
public:
    AndFilter(const std::vector<Filter<T>*>& filters): LogicalFilter<T>(filters) {};
    bool matches(const T& item) const override
    {
        for(Filter<T>* filter : this->_filters) {
            if (!filter->matches(item)) {
                return false;
            }
        }
        return true;   
    }
    std::string getFilterName() const override
    {
        return "AndFilter";
    }
    void printDescription(std::ostream& out) const override
    {
        out << "AndFilter: all filters must match";
        for(Filter<T>* filter : this->_filters) {
            filter->printDescription(out);
        }
    }
};

template<typename T> 
class OrFilter : public LogicalFilter<T> {
public:
    OrFilter(const std::vector<Filter<T>*>& filters): LogicalFilter<T>(filters) {};
    bool matches(const T& item) const override
    {
        for(Filter<T>* filter : this->_filters) {
            if (!filter->matches(item)) {
                return true;
            }
        }
        return false;   
    }
    std::string getFilterName() const override
    {
        return "OrFilter";
    }
    void printDescription(std::ostream& out) const override
    {
        out << "OrFilter: all filters must match";
        for(Filter<T>* filter : this->_filters) {
            filter->printDescription(out);
        }
    }
};

// ----------------------

template<typename T>
class Collection {
    std::vector<T> data_;
public:
    std::vector<Filter<T>*> filters_;

    void add(const T& item){
        data_.push_back(item);
    }
    void addfilter(Filter<T>* filter){
        filters_.push_back(filter);
    }
    size_t size() const
    {
        return data_.size();
    }
    void remove(size_t idx)
    {
        std::swap(data_[idx], data_[data_.size() - 1]);
        data_.pop_back();
    }
    void readFromStream(std::istream& in, size_t count)
    {
        for(size_t i = 0; i < count; ++i) {
            T item;
            in >> item;
            data_.push_back(item);
        }
    }
    void writeToStream(std::ostream& out) const
    {
        for(const T& item : data_) {
            out << item << " ";
        }
        out << std::endl;
    }

    size_t matchCount() const
    {
        size_t count = 0;
        AndFilter<T> andFilter(filters_);
        for(const T& item : data_) {
            if (andFilter.matches(item)) {
                ++count;
            }
        }
        return count;
    }
    double matchPercent() const
    {
        return (matchCount() / data_.size()) *100;
    }
    void writeMatches(std::ostream& out) const
    {
        for(const T& item: data_)
        {
            bool match = true;
            for(auto filter: filters_)
            {
                if(!filter->matches(item))
                {
                    match = false;
                    break;
                }
            }
            if(match)
                out << item << " ";
        }
    }
};

template<typename T>
Filter<T>* NumericFilterCreator(FilterType type)
{
    switch (type)
    {
        case FilterType::IntervalFilter:
        {
            double lo, hi;
            cout<<" Enter the lower bound: "; cin>>lo;
            cout<<" Enter the upper bound: "; cin>>hi;
            return new IntervalFilter<T>(lo, hi);
        }
        case FilterType::DivisibleFilter:
        {
            T divisor;
            cout<<" Enter the divisor: "; cin>>divisor;
            return new DivisibleFilter(divisor);
        }
        case FilterType::EvenFilter:
            return new EvenFilter<T>();
        default: 
            return nullptr;
    }
}

// template<typename T>
// Filter<T>* StringFilterCreator(const std::string& filterName) {
//     switch(filterName)
//     {
//         case "LettersFilter":
//         {
//             std::string allowed;
//             cout<<" Enter the allowed letters: "; cin>>allowed;
//             return new LettersFilter(allowed);
//         }
//         case "UpperFilter":
//             return new UpperFilter();
//         case "LowerFilter":
//             return new LowerFilter();
//         default: 
//             return nullptr;
//         };
//     }
//     template<typename T>
//     Filter<T>* PredefinedFilterCreator(const std::string& filterName) {
//         switch(filterName)
//         {
//             case "BlackListFilter":
//             {
//                 std::vector<T> forbidden;
//                 size_t n;
//             cout<< " Enter number of forbidden items: "; cin>>n;
//             cout<<" Enter the forbidden items: ";
//             T item;
//             for(size_t i = 0; i < n; ++i) {
//                 forbidden.push_back(item);
//             }
//             return new BlackListFilter<T>(forbidden);
//         }
//         case "WhiteListFilter":
//         {
//             std::vector<T> allowed;
//             size_t n;
//             cout<< " Enter number of allowed items: "; cin>>n;
//             cout<<" Enter the allowed items: ";
//             T item;
//             for(size_t i = 0; i < n; ++i) {
//                 allowed.push_back(item);
//             }
//             return new WhiteListFilter<T>(allowed);
//         }
//         default: 
//             return nullptr;
//     }   
// }

// template<typename T>
// Filter<T>* LogicalFilterCreator(const std::string& filterName) {
//     switch(filterName)
//     {
//         case "AndFilter":
//         {
//             std::vector<Filter<T>*> filters;   
//             size_t n;
//             cout<< " Enter number of filters: "; cin>>n;
//             for(size_t i = 0; i < n; ++i) {
//                 cout<<" Enter filter name: ";
//                 std::string filterName;
//                 cin>>filterName;
//                 Filter<T>* filter = FilterCreator<T>(filterName);
//                 filters.push_back(filter);
//             }
//             return new AndFilter<T>(filters);
//         }
//         case "orFilter":
//         {
//             std::vector<Filter<T>*> filters;   
//             size_t n;
//             cout<< " Enter number of filters: "; cin>>n;
//             for(size_t i = 0; i < n; ++i) {
//                 cout<<" Enter filter name: ";
//                 std::string filterName;
//                 cin>>filterName;
//                 Filter<T>* filter = FilterCreator<T>(filterName);
//                 filters.push_back(filter);
//             }
//             return new AndFilter<T>(filters);
//         }
//         default:
//             return nullptr;
//     };
// }

const std::map<std::string, FilterType> stringToEnum = { {"IntervalFilter", FilterType::IntervalFilter}, {"EvenFilter", FilterType::EvenFilter}, {"DivisibleFilter", FilterType::DivisibleFilter}};

int main(){
    Collection<int> coll;
    for(int i = 0; i<100; i++)
        coll.add(i);
    for( int i = 0 ; i < 3; i++)
    {
        std::string filterName;
        cin>>filterName;
        if(stringToEnum.find(filterName) != stringToEnum.end())
            coll.addfilter(NumericFilterCreator<int>(stringToEnum.at(filterName)));
    }
    coll.writeMatches(std::cout);
}


/*
IntervalFilter
10
50
EvenFilter
DivisibleFilter
3
*/