#include <initializer_list>
#include <iostream>
#include <cassert>

class Set;
class Node;
std::ostream &operator<<( std::ostream &out, Set const &rhs );


class Node 
{
  public:
    Node( int new_value, Node *new_next );
    int   value() const;
    Node *next()  const;

  private:
    int value_;
    Node *next_;

  friend class Set;
};

Node::Node( int new_value, Node *new_next ) : value_(new_value), next_(new_next) {}

int Node::value() const 
{ 
    return value_; 
}

Node *Node::next() const 
{ 
    return next_; 
}


class Set 
{
  public:
    Set( std::initializer_list<int> initial_values );
   ~Set();

    Set( Set const &orig );
    Set( Set      &&orig );

    Set &operator=( Set const &orig );
    Set &operator=( Set      &&orig );

    bool        empty() const;
    std::size_t size()  const;

    void clear();
    Node *find( int const &item ) const;

    std::size_t insert( int const &item );
    std::size_t insert( int const array[], std::size_t const begin, std::size_t const end );

    std::size_t erase( int const &item );

    std::size_t merge( Set &other );

    Set &operator|=( Set const &other );
    Set &operator&=( Set const &other );
    Set &operator^=( Set const &other );
    Set &operator-=( Set const &other );

    Set operator|( Set const &other ) const;
    Set operator&( Set const &other ) const;
    Set operator^( Set const &other ) const;
    Set operator-( Set const &other ) const;

    bool operator<=( Set const &other ) const;
    bool operator>=( Set const &other ) const;
    bool operator<( Set const &other ) const;
    bool operator>( Set const &other ) const;

    bool operator==( Set const &other ) const;
    bool operator!=( Set const &other ) const;

  private:
    Node *p_head_;

  friend std::ostream &operator<<( std::ostream &out, Set const &rhs );
};



Set::Set( std::initializer_list<int> initial_values ) : p_head_(nullptr)
{
    for (int val : initial_values)
    {
        insert(val);
    }
}

Set::~Set()
{
    clear();
}


// Copy constructor
Set::Set( Set const &orig ) : p_head_(nullptr )
{
    for (Node *ptr = orig.p_head_; ptr; ptr = ptr->next_)
    {
        insert(ptr->value_);
    }
}

// Move constructor
Set::Set( Set &&orig ) : p_head_(orig.p_head_)
{
    orig.p_head_ = nullptr;
}


// Copy assignment
Set &Set::operator=( Set const &orig )
{
    if (this != &orig)
    {
        clear();
        for (Node *ptr = orig.p_head_; ptr; ptr = ptr->next_)
        {
            insert(ptr->value_);
        }
    }
    return *this;
}

// Move assignment
Set &Set::operator=( Set &&orig )
{
    if (this != &orig)
    {
        clear();
        p_head_ = orig.p_head_;
        orig.p_head_ = nullptr;
    }
    return *this;
}


bool Set::empty() const 
{ 
    return p_head_ == nullptr; 
}

std::size_t Set::size() const
{
    std::size_t count = 0;
    for (Node* ptr = p_head_; ptr; ptr = ptr->next_)
    {
        ++count;
    }
    return count;
}

void Set::clear()
{
    while (p_head_)
    {
        Node* temp = p_head_;
        p_head_ = p_head_->next_;
        delete temp;
    }
}

Node *Set::find( int const &item ) const
{
    for (Node* ptr = p_head_; ptr; ptr = ptr->next_)
    {
        if (ptr->value_ == item)
        {
            return ptr;
        }
    }
    return nullptr;
}


std::size_t Set::insert( int const &item )
{
    if (find(item))
    {
        return 0;
    }
    p_head_ = new Node(item, p_head_);
    return 1;
}

std::size_t Set::insert( int const array[], std::size_t const begin, std::size_t const end )
{
    std::size_t count = 0;
    for (std::size_t i = begin; i < end; ++i)
    {
        count += insert(array[i]);
    }
    return count;
}

std::size_t Set::erase( int const &item )
{
    Node *curr = p_head_;
    Node *prev = nullptr;

    while (curr)
    {
        if (curr->value_ == item)
        {
            if (prev)
            {
                prev->next_ = curr->next_;
            }
            else
            {
                p_head_ = curr->next_;
            }
            delete curr;
            return 1;
        }
        prev = curr;
        curr = curr->next_;
    }
    return 0;
}


std::size_t Set::merge( Set &other )
{
    if (&other == this)
    {
        return 0;
    }

    std::size_t count = 0;

    Node *curr = other.p_head_;
    Node *prev = nullptr;

    while (curr)
    {
        if (find(curr->value_) == nullptr)
        {
            Node *next_node = curr->next_;

            if (prev)
            {
                prev->next_ = curr->next_;
            }
            else
            {
                other.p_head_ = curr->next_;
            }

            curr->next_ = p_head_;
            p_head_ = curr;
            curr = next_node;
            ++count;
        }
        else
        {
            prev = curr;
            curr = curr->next_;
        }
    }

    return count;
}


Set &Set::operator|=( Set const &other )
{
    for (Node *ptr = other.p_head_; ptr; ptr = ptr->next_)
    {
        insert(ptr->value_);
    }
    return *this;
}

Set &Set::operator&=( Set const &other )
{
    Node *curr = p_head_;
    Node *prev = nullptr;

    while (curr)
    {
        if (!other.find(curr->value_))
        {
            Node *temp = curr;
            if (prev)
            {
                prev->next_ = curr->next_;
            }
            else
            {
                p_head_ = curr->next_;
            }
            curr = curr->next_;
            delete temp;
        }
        else
        {
            prev = curr;
            curr = curr->next_;
        }
    }
    return *this;
}

Set &Set::operator^=( Set const &other )
{
    for (Node *ptr = other.p_head_; ptr; ptr = ptr->next_)
    {
        if (find(ptr->value_))
        {
            erase(ptr->value_);
        }
        else
        {
            insert(ptr->value_);
        }
    }
    return *this;
}

Set &Set::operator-=( Set const &other )
{
    for (Node *ptr = other.p_head_; ptr; ptr = ptr->next_)
    {
        erase(ptr->value_);
    }
    return *this;
}


// Versions that return new sets
Set Set::operator|( Set const &other ) const
{
    Set result{};
    result |= *this;
    result |= other;
    return result;
}

Set Set::operator&( Set const &other ) const
{
    Set result{};
    for (Node *ptr = p_head_; ptr; ptr = ptr->next_)
    {
        if (other.find(ptr->value_))
        {
            result.insert(ptr->value_);
        }
    }
    return result;
}

Set Set::operator^( Set const &other ) const
{
    Set result{};
    for (Node *ptr = p_head_; ptr; ptr = ptr->next_)
    {
        if (!other.find(ptr->value_))
        {
            result.insert(ptr->value_);
        }
    }
    for (Node *ptr = other.p_head_; ptr; ptr = ptr->next_)
    {
        if (!find(ptr->value_))
        {
            result.insert(ptr->value_);
        }
    }
    return result;
}

Set Set::operator-( Set const &other ) const
{
    Set result{};
    for (Node *ptr = p_head_; ptr; ptr = ptr->next_)
    {
        if (!other.find(ptr->value_))
        {
            result.insert(ptr->value_);
        }
    }
    return result;
}


bool Set::operator<=( Set const &other ) const
{
    for (Node *ptr = p_head_; ptr; ptr = ptr->next_)
    {
        if (!other.find(ptr->value_))
        {
            return false;
        }
    }
    return true;
}

bool Set::operator>=( Set const &other ) const
{
    return other <= *this;
}

bool Set::operator<( Set const &other ) const
{
    return (*this <= other) && (size() < other.size());
}

bool Set::operator>( Set const &other ) const
{
    return (other <= *this) && (other.size() < size());
}


bool Set::operator==( Set const &other ) const
{
    return size() == other.size() && (*this <= other);
}

bool Set::operator!=( Set const &other ) const
{
    return !(*this == other);
}


std::ostream &operator<<( std::ostream &out, Set const &rhs )
{
    out << "{";
    if (!rhs.empty())
    {
        out << rhs.p_head_->value();
        for (Node *ptr = rhs.p_head_->next(); ptr; ptr = ptr->next())
        {
            out << ", " << ptr->value();
        }
    }
    out << "}";
    return out;
}