#ifndef __QUERY_HPP__
#define __QUERY_HPP__

#include "TextQuery.hpp"

namespace wd
{

//查询类的抽象基类
class Query_base
{
    friend class Query;
protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;
private:
    //返回当前Query匹配的QueryResult
    virtual QueryResult eval(const TextQuery &) const = 0;
    //rep是表示查询的一个string
    virtual string rep() const = 0;
};


//是一个接口类，指向Query_base派生类的对象
//是一个管理Query_base继承体系接口的类
class Query
{
    //运算符需要访问Query的私有构造函数
    friend Query operator~(const Query &);
    friend Query operator|(const Query &, const Query &);
    friend Query operator&(const Query &, const Query &);
    
public:
    //构建一个新的WordQuery
    Query(const string &s);

    QueryResult eval(const TextQuery &t) const
    {   return _q->eval(t);  }

    string rep() const
    {   return _q->rep();   }

private:
    Query(shared_ptr<Query_base> query)
    :_q(query)
    {}

    shared_ptr<Query_base> _q;
};

//是一个抽象基类
//用于查找一个给定的string，是执行查询的唯一操作，在给定的TextQuery对象上
//所有成员都是私有的
class WordQuery
:public Query_base
{
    friend class Query;//Query接口可以访问WordQuery的构造函数
    
    WordQuery(const string &s)
    :_query_word(s)
    {}

    QueryResult eval(const TextQuery &t) const override
    {   return t.query(_query_word);     }

    string rep() const override
    {   return _query_word;  }

    string _query_word;
};

//是一个抽象基类
//保存一个需要对其取反的query接口
//所有成员都是私有的
class NotQuery
:public Query_base
{
    friend Query operator~(const Query &);
    NotQuery(const Query &q)
    :_query(q)
    {}

    string rep() const override
    {   return "~(" + _query.rep() + ")";    }

    QueryResult eval(const TextQuery &) const override;

    Query _query;
};

inline Query operator~(const Query &operand)
{
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

//是一个抽象基类
//不定义eval
class BinaryQuery
:public Query_base
{
protected:
    BinaryQuery(const Query &lhs, const Query &rhs, string s)
    :_lhs(lhs)
    ,_rhs(rhs)
    ,_opSym(s)
    {}

    string rep() const override
    {   return "(" + _lhs.rep() + " " + _opSym + " " + _rhs.rep() + ")";    }

    //两侧的操作对象
    Query _lhs;
    Query _rhs;
    //运算符名字
    string _opSym;
};

class AndQuery
:public BinaryQuery
{
    friend Query operator&(const Query &, const Query&);
    AndQuery(const Query &left, const Query &right)
    :BinaryQuery(left, right, "&")
    {}

    QueryResult eval(const TextQuery &) const override;
};

class OrQuery
:public BinaryQuery
{
    friend Query operator|(const Query &lhs, const Query &rhs);

    OrQuery(const Query &lhs, const Query &rhs)
    :BinaryQuery(lhs, rhs, "|")
    {}

    QueryResult eval(const TextQuery &) const override;
};

inline Query operator&(const Query &lhs, const Query &rhs)
{
    return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

inline Query operator|(const Query &lhs, const Query &rhs)
{
    return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

}// end of namespace wd

#endif
