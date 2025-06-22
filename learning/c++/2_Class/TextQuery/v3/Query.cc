#include "Query.hpp"
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;

namespace wd
{

QueryResult TextQuery::query(const string &sought) const
{
    static shared_ptr<set<line_no>> nodate(new set<line_no>);

    auto loc = _word2number.find(sought);
    if (loc == _word2number.end()) {
        return QueryResult(sought, nodate, _lines);
    }
    else {
        return QueryResult(sought, loc->second, _lines);
    }

}

std::ostream& operator<<(std::ostream &os, const Query &query)
{
    return os << query.rep();
}

Query::Query(const string &s)
:_q(new WordQuery(s))
{}


QueryResult OrQuery::eval(const TextQuery &text) const
{
    auto left = _lhs.eval(text);
    auto right = _rhs.eval(text);

    auto ret_lines = std::make_shared<set<line_no>>(left.begin(), left.end());
    ret_lines->insert(right.begin(), right.end());
    return QueryResult(rep(), ret_lines, left.get_lines());
}

QueryResult AndQuery::eval(const TextQuery &text) const
{
    auto left = _lhs.eval(text);
    auto right = _rhs.eval(text);

    auto ret_lines = std::make_shared<set<line_no>>();

    std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));

    return QueryResult(rep(), ret_lines, left.get_lines());
}

QueryResult NotQuery::eval(const TextQuery &text) const
{
    //通过Query运算对象对eval进行虚调用
    auto result = _query.eval(text);
    
    auto ret_lines = std::make_shared<set<line_no>>();

    auto beg = result.begin();
    auto end = result.end();

    auto sz = result.get_lines()->size();
    for (size_t n = 0; n < sz; ++n) {
        if (beg == end || *beg != n) {
            ret_lines->insert(n);
        }
        else if (beg != end) {
            ++beg;
        }
    }

    return QueryResult(rep(), ret_lines, result.get_lines());
}


}// end of namespace wd
