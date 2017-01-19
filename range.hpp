/*
    Range-based for Support.
    Licensed under the Mozilla Public License 2.0 (See LICENSE or https://opensource.org/licenses/MPL-2.0).
    Copyright (C) 2017 SiLeader. All rights reserved.
*/

#ifndef SILEADER_RANGE_RANGE_HPP
#define SILEADER_RANGE_RANGE_HPP

#include <vector>
#include <type_traits>
#include <functional>

namespace range {
    template<class T, class Allocator=std::allocator<T>>class range {
    public:
        using range_type=::range::range<T, Allocator>;
        using container_type=std::vector<T, Allocator>;
        using reference=typename container_type::reference;
        using const_reference=typename container_type::const_reference;
        using size_type=typename container_type::size_type;
        using difference_type=typename container_type::difference_type;
        using value_type=typename container_type::value_type;
        using pointer=typename container_type::pointer;
        using const_pointer=typename container_type::const_pointer;
        using iterator=typename container_type::iterator;
        using const_iterator=typename container_type::const_iterator;
        using reverse_iterator=typename container_type::reverse_iterator;
        using const_reverse_iterator=typename container_type::const_reverse_iterator;
    private:
        container_type m_container;
    public:
        /* constructors */
        range()=default;
        range(const range&)=default;
        range(range&&)=default;

        range(const container_type& container) : m_container(container) {}
        range(container_type&& container) : m_container(container) {}
        template<std::size_t N>range(const T arr[N]) : m_container(std::begin(arr), std::end(arr)) {}

        range(std::initializer_list<T> ilist) : m_container(ilist) {}
        range(const T& start, const T& last) {
            for(T i=start; i!=last; ++i) {
                m_container.push_back(i);
            }
        }
        range(const T& start, const T& last, const T& diff) {
            for(T i=start; i!=last; i+=diff) {
                m_container.push_back(i);
            }
        }
        range(std::size_t count, const T& start, bool is_increment=true) {
            T val=start;
            for(std::size_t i=0; i<count; ++i) {
                m_container.push_back(val);
                if(is_increment) {
                    ++val;
                }
            }
        }
        range(std::size_t count, std::function<T()> generator) {
            for(std::size_t i=0; i<count; ++i) {
                m_container.push_back(generator());
            }
        }
        range(std::size_t count, std::function<T(std::size_t)> generator) {
            for(std::size_t i=0; i<count; ++i) {
                m_container.push_back(generator(i));
            }
        }

        /* assign operators */
        range& operator=(const range& rhs)=default;
        range& operator=(range&& rhs)=default;

        range& operator=(std::initializer_list<T> ilist) {
            m_container=ilist;
            return *this;
        }
        range& operator=(const container_type& rhs) {
            m_container=rhs;
            return *this;
        }
        range& operator=(container_type&& rhs) {
            m_container=rhs;
            return *this;
        }

        range& reverse() {
            container_type tmp(m_container.rbegin(), m_container.rend());
            std::swap(m_container, tmp);
            return *this;
        }

        range& convert(std::function<T(T)> f) {
            for(auto&& v : m_container) {
                v=f(v);
            }
            return *this;
        }

        range map(std::function<T(T)> f)const {
            return range(this->size(), [&](std::size_t i){
                return f(m_container[i]);
            });
        }
        template<class R> R reduce(std::function<R(range_type)> f)const {
            return f(*this);
        }

        range& for_each(std::function<void(T&)> f) {
            for(auto&& v : m_container) {
                f(v);
            }
            return *this;
        }

        range& assign(std::size_t count, std::function<T()> generator) {
            m_container.clear();
            for(std::size_t i=0; i<count; ++i) {
                m_container.push_back(generator());
            }
            return *this;
        }
        range& assign(std::size_t count, std::function<T(std::size_t)> generator) {
            m_container.clear();
            for(std::size_t i=0; i<count; ++i) {
                m_container.push_back(generator(i));
            }
            return *this;
        }

        /* std::vector functions */
        auto begin() noexcept -> iterator {
            return m_container.begin();
        }
        auto begin() const noexcept -> const_iterator {
            return m_container.begin();
        }
        auto cbegin() const noexcept -> const_iterator {
            return m_container.cbegin();
        }
        auto rbegin() noexcept -> reverse_iterator {
            return m_container.rbegin();
        }
        auto rbegin() const noexcept -> const_reverse_iterator {
            return m_container.rbegin();
        }
        auto crbegin() const noexcept -> const_reverse_iterator {
            return m_container.crbegin();
        }

        auto end() noexcept -> iterator {
            return m_container.end();
        }
        auto end() const noexcept -> const_iterator {
            return m_container.end();
        }
        auto cend() const noexcept -> const_iterator {
            return m_container.cend();
        }
        auto rend() noexcept -> reverse_iterator {
            return m_container.rend();
        }
        auto rend() const noexcept -> const_reverse_iterator {
            return m_container.rend();
        }
        auto crend() const noexcept -> const_reverse_iterator {
            return m_container.crend();
        }

        size_type size() const noexcept {
            return m_container.size();
        }
        size_type max_size() const noexcept {
            return m_container.max_size();
        }
        range& resize(size_type size) {
            m_container.resize(size);
            return *this;
        }
        range& resize(size_type size, const T& val) {
            m_container.resize(size, val);
            return *this;
        }
        size_type capacity() const {
            return m_container.capacity();
        }
        bool empty() const noexcept {
            return m_container.empty();
        }
        range& reserve(size_type n) {
            m_container.reserve(n);
            return *this;
        }
        range& shrink_to_fit() {
            m_container.shrink_to_fit();
            return *this;
        }

        reference operator[](size_type n) {
            return m_container[n];
        }
        const_reference operator[](size_type n) const {
            return m_container[n];
        }
        reference at(size_type n) {
            return m_container.at(n);
        }
        const_reference at(size_type n) const {
            return m_container.at(n);
        }
        T* data() noexcept {
            if(this->empty())return nullptr;
            return m_container.data();
        }
        const T* data() const noexcept {
            if(this->empty())return nullptr;
            return m_container.data();
        }
        reference front() {
            return m_container.front();
        }
        const_reference front() const {
            return m_container.front();
        }
        reference back() {
            return m_container.back();
        }
        const_reference back() const {
            return m_container.back();
        }

        template<class InputIterator> range& assign(InputIterator first, InputIterator last) {
            m_container.assign(first, last);
            return *this;
        }
        range& assign(size_type n, const_reference val, bool is_increment=false) {
            if(is_increment) {
                T v=val;
                this->assign(n, [&](std::size_t idx) {
                    return v++;
                });
            }else{
                m_container.assign(n, val);
            }
            return *this;
        }
        range& assign(std::initializer_list<T> ilist) {
            m_container.assign(ilist);
            return *this;
        }
        range& push_back(const_reference val) {
            m_container.push_back(val);
            return *this;
        }
        range& push_back(T&& val) {
            m_container.push_back(val);
            return *this;
        }
        template<class... Args>range& emplace_back(Args&&... args) {
            m_container.emplace_back(args...);
            return *this;
        }
        range& pop_back() {
            m_container.pop_back();
            return *this;
        }
        iterator insert(const_iterator pos, const_reference val) {
            return m_container.insert(pos, val);
        }
        iterator insert(const_iterator pos, T&& val) {
            return m_container.insert(pos, val);
        }
        iterator insert(const_iterator pos, size_type n, const T& val) {
            return m_container.insert(pos, n ,val);
        }
        template <class InputIterator> iterator insert(const_iterator pos, InputIterator first, InputIterator last) {
            return m_container.insert(pos, first, last);
        }
        iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
            return m_container.insert(pos, ilist);
        }
        template <class... Args> iterator emplace(const_iterator pos, Args&&... args) {
            return m_container.emplace(pos, args...);
        }
        iterator erase(const_iterator pos) {
            return m_container.erase(pos);
        }
        iterator erase(const_iterator first, const_iterator last) {
            return m_container.erase(first, last);
        }
        range& swap(std::vector<T>& val) {
            m_container.swap(val);
            return *this;
        }
        range& swap(range& val) {
            return swap(val.m_container);
        }
        range& clear() {
            m_container.clear();
            return *this;
        }

        typename container_type::allocator_type get_allocator() const noexcept {
            return m_container.get_allocator();
        }

        /* Compare operators */
        bool operator==(const range& rhs) const {
            return m_container==rhs.m_container;
        }
        bool operator!=(const range& rhs) const {
            return m_container!=rhs.m_container;
        }
        bool operator<(const range& rhs) const {
            return m_container<rhs.m_container;
        }
        bool operator<=(const range& rhs) const {
            return m_container<=rhs.m_container;
        }
        bool operator>(const range& rhs) const {
            return m_container>rhs.m_container;
        }
        bool operator>=(const range& rhs) const {
            return m_container>=rhs.m_container;
        }
    };
} /* range */

#endif /* end of include guard: SILEADER_RANGE_RANGE_HPP */
