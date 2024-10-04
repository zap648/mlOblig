#ifndef TQUADTRE_H
#define TQUADTRE_H

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <iterator>
typedef std::pair<double, double> Point2D;

struct GameObject
{
    Point2D m_position;
    std::string m_navn;
    GameObject() {/* pass på å HUGSA detta! */}
    GameObject(const Point2D& position, std::string navn)
        : m_position{position}, m_navn{navn} { }
    // Point2D getPosition() const { return m_position; }
};

template <class ID, class T>
class QuadTre;

template <class ID, class T>
class iterator : public std::iterator<std::output_iterator_tag, T>
{
public:
    explicit iterator(QuadTre<ID, T>& quadtre, size_t index=0);
    T operator*() const;
    iterator & operator++();
    iterator operator++(T);
private:
    size_t mIndex{0};
    QuadTre<ID, T>& quadTre;
};

template <class ID, class T>
class QuadTre
{
private:
    Point2D m_a;
    Point2D m_b;
    Point2D m_c;
    Point2D m_d;

    QuadTre* m_sv;
    QuadTre* m_so;
    QuadTre* m_nv;
    QuadTre* m_no;

    std::list<std::pair<ID, T>> m_objects;

    bool isLeaf() const;

    std::vector<T> m_all_objects;

    void traverse_all(std::vector<T>& all_objects);

public:
    QuadTre();
    QuadTre(const Point2D &v1, const Point2D &v2, const Point2D &v3, const Point2D &v4);
    void subDivide(int n);
    void print() const;
    void print_all() const;
    QuadTre* insert(const Point2D& point, const ID& id, const T& object);
    QuadTre* find(const Point2D& p);
    const QuadTre* find(const Point2D& p) const;
    T& find(const ID& id);
    T& operator[] (ID id);

    typename std::vector<T>::iterator begin()
    {
        traverse_all(m_all_objects);
        return m_all_objects.begin();
    }
    typename std::vector<T>::iterator end()
    {
        return m_all_objects.end();
    }
};

template <class ID, class T>
void QuadTre<ID, T>::subDivide(int n)
{
    if (n>0)
    {
        Point2D v1 = Point2D{(m_a.first + m_b.first)/2, (m_a.second + m_b.second)};
        Point2D v2 = Point2D{(m_b.first + m_c.first)/2, (m_b.second + m_c.second)};
        Point2D v3 = Point2D{(m_c.first + m_d.first)/2, (m_c.second + m_d.second)};
        Point2D v4 = Point2D{(m_d.first + m_a.first)/2, (m_d.second + m_a.second)};
        Point2D m = Point2D{(m_a.first + m_c.first)/2, (m_a.second + m_c.second)};

        m_sv = new QuadTre(m_a, v1, m, v4);
        m_sv->subDivide(n-1);
        m_so = new QuadTre(v1, m_b, v2, m);
        m_sv->subDivide(n-1);
        m_no = new QuadTre(m, v2, m_c, v3);
        m_no->subDivide(n-1);
        m_nv = new QuadTre(v4, m, v3, m_d);
        m_nv = subDivide(n-1);
    }
}

template <class ID, class T>
QuadTre<ID, T>* QuadTre<ID, T>::insert(const Point2D& point, const ID& id, const T& gameObject)
{
    if (isLeaf())
    {
        m_objects.push_back(std::pair<ID, T>{id, gameObject});
        return this;
    }
    else
    {
        Point2D m = Point2D{(m_a.first + m_c.first)/2, (m_a.second + m_c.second)/2};

        if (point.second > m.second)
        {
            if (point.first < m.first)
                m_sv->insert(point, id, gameObject);
            else
                m_so->insert(point, id, gameObject);
        }
        else
        {
            if (point.first < m.first)
                m_nv->insert(point, id, gameObject);
            else
                m_no->insert(point, id, gameObject);
        }
    }
}

template <class ID, class T>
QuadTre<ID, T>* QuadTre<ID, T>::find(const Point2D& p)
{
    if (isLeaf())
    {
        return this;
    }
    else {
        Point2D m = Point2D{(m_a.first + m_c.first)/2, (m_a.second + m_c.second)/2};

        if (p.second < m.second)
        {
            if (p.first < m.first)
                m_sv->find(p);
            else
                m_so->find(p);
        }
        else
        {
            if (p.first < m.first)
                m_nv->find();
            else
                m_no->find(p);
        }
    }
}

template <class ID, class T>
const QuadTre<ID, T> *QuadTre<ID, T>::find(const Point2D& p) const
{
    if (isLeaf())
    {
        return this;
    }
    else
    {
        Point2D m = Point2D{(m_a.first + m_c.first)/2, (m_a.second + m_c.second)/2};

        if (p.second < m.second)
        {
            if (p.first < m.first)
                m_sv->find(p);
            else
                m_so->find(p);
        }
        else
        {
            if (p.first < m.first)
                m_nv->find();
            else
                m_no->find(p);
        }
    }
}

template <class ID, class T>
T& QuadTre<ID, T>::find(const ID& id)
{
    if (isLeaf() && m_objects.size()>0)
    {
        for (auto it = m_objects.begin(); it != m_objects.end(); it++)
        {
            if (it->first == id)
                return it->second;
        }
    }
    else if (m_no)
        m_no->find(id);
    else if (m_nv)
        m_nv->find(id);
    else if (m_sv)
        m_sv->find(id);
    else if (m_so)
        m_so->find(id);
}

template <class ID, class T>
T& QuadTre<ID, T>::operator[] (ID id)
{
    if (isLeaf())
    {
        for (auto it = m_objects.begin(); it != m_objects.end(); it++)
        {
            if (it->first == id)
                return it->second;
        }
    }
}

template <class ID, class T>
void QuadTre<ID, T>::traverse_all(std::vector<T> &all_objects)
{
    for (auto it = m_objects.begin(); it != m_objects.end(); it++)
        all_objects.push_back(it->second);
    if (m_no) m_no->traverse_all(all_objects);
    if (m_nv) m_nv->traverse_all(all_objects);
    if (m_sv) m_sv->traverse_all(all_objects);
    if (m_so) m_sv->traverse_all(all_objects);
}

#endif // TQUADTRE_H
