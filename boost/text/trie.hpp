#ifndef BOOST_TEXT_TRIE_HPP
#define BOOST_TEXT_TRIE_HPP

#include <boost/optional.hpp>
#include <boost/text/string_view.hpp>

#include <memory>
#include <type_traits>
#include <vector>


namespace boost { namespace trie {

    // TODO: Consider an optimization that creates a single node for long
    // nonbranching chains of nodes.

    // TODO: Remove key storage in the nodes; rebuild the key as necessary in
    // const_trie_iterator::operator*().

    // TODO: Add a custom optional-like proxy type for the return type of
    // mutable operator[] so that these are all well-formed:
    // if (trie["foo"]) ...
    // trie["foo"] = 1;
    // auto const value = trie["foo"];

    template<typename Key, typename Value>
    struct trie_iterator;

    template<typename Key, typename Value>
    struct const_trie_iterator;

    template<typename Key, typename Value>
    struct reverse_trie_iterator;

    template<typename Key, typename Value>
    struct const_reverse_trie_iterator;

    template<typename Key, typename Value>
    struct trie_element
    {
        Key key;
        Value value;

        friend bool
        operator==(trie_element const & lhs, trie_element const & rhs)
        {
            return lhs.key == rhs.key && lhs.value == rhs.value;
        }
        friend bool
        operator!=(trie_element const & lhs, trie_element const & rhs)
        {
            return !(lhs == rhs);
        }
    };

    template<typename Key, typename Value>
    struct trie_range
    {
        using iterator = trie_iterator<Key, Value>;

        iterator first;
        iterator last;

        iterator begin() const { return first; }
        iterator end() const { return last; }

        friend bool operator==(trie_range const & lhs, trie_range const & rhs)
        {
            return lhs.first == rhs.first && lhs.last == rhs.last;
        }
        friend bool operator!=(trie_range const & lhs, trie_range const & rhs)
        {
            return !(lhs == rhs);
        }
    };

    template<typename Key, typename Value>
    struct const_trie_range
    {
        using const_iterator = const_trie_iterator<Key, Value>;

        const_iterator first;
        const_iterator last;

        const_iterator begin() const { return first; }
        const_iterator end() const { return last; }

        friend bool
        operator==(const_trie_range const & lhs, const_trie_range const & rhs)
        {
            return lhs.first == rhs.first && lhs.last == rhs.last;
        }
        friend bool
        operator!=(const_trie_range const & lhs, const_trie_range const & rhs)
        {
            return !(lhs == rhs);
        }
    };

    template<typename Key, typename Value>
    struct trie_insert_result
    {
        trie_iterator<Key, Value> iter;
        bool inserted;

        friend bool operator==(
            trie_insert_result const & lhs, trie_insert_result const & rhs)
        {
            return lhs.iter == rhs.iter && lhs.inserted == rhs.inserted;
        }
        friend bool operator!=(
            trie_insert_result const & lhs, trie_insert_result const & rhs)
        {
            return !(lhs == rhs);
        }
    };

    namespace detail {

        template<typename Key, typename Value>
        struct trie_node_t;

        template<typename Key, typename Value>
        struct trie_iterator_state_t
        {
            trie_node_t<Key, Value> const * parent_;
            std::size_t index_; // TODO: Iterator instead.
        };

        // TODO: Perform an audit to see where calls to this function can be
        // minimized (such as in the const_trie_iterator::operator{++,--}(().
        template<typename Key, typename Value>
        trie_iterator_state_t<Key, Value>
        parent_state(trie_iterator_state_t<Key, Value> state)
        {
            auto const new_parent = state.parent_->parent();
            auto const it = std::find_if(
                new_parent->begin(),
                new_parent->end(),
                [state](std::unique_ptr<trie_node_t<Key, Value>> const & ptr) {
                    return ptr.get() == state.parent_;
                });
            return {new_parent, std::size_t(it - new_parent->begin())};
        }

#if 0 // TODO: Use this instead!  The parent's child list could be arbitrarily
      // large!  This means adding a Compare template parameter and data member
      // to every iterator, though. :(
        template<typename Key, typename Value, typename Compare>
        trie_iterator_state_t<Key, Value> parent_state(
            trie_iterator_state_t<Key, Value> state, Compare const & comp)
        {
            auto const new_parent = state.parent_->parent_;
            auto const it = new_parent->lower_bound(state.parent_->e_, comp);
            return {new_parent, it - new_parent->children_.begin()};
        }
#endif

        template<typename Key, typename Value>
        trie_node_t<Key, Value> const *
        to_node(trie_iterator_state_t<Key, Value> state)
        {
            if (state.index_ < state.parent_->size())
                return state.parent_->child(state.index_);
            return nullptr;
        }

    }

    template<typename Key, typename Value>
    struct trie_match_result
    {
        detail::trie_node_t<Key, Value> const * node;
        std::ptrdiff_t size;
        bool match;

        friend bool
        operator==(trie_match_result const & lhs, trie_match_result const & rhs)
        {
            return lhs.node == rhs.node && lhs.size == rhs.size &&
                   lhs.match == rhs.match;
        }
        friend bool
        operator!=(trie_match_result const & lhs, trie_match_result const & rhs)
        {
            return !(lhs == rhs);
        }
    };

    // TODO: KeyIter, KeyRange, and Range concepts.
    // TODO: Key concept specifying that Key is a container.
    // TODO: Compare concept specifying that Compare compares Key::value_types.
    // Don't forget to mention that Compare must be statically polymorphic.
    template<typename Key, typename Value, typename Compare = std::less<>>
    struct trie
    {
    private:
        using node_t = detail::trie_node_t<Key, Value>;
        using iter_state_t = detail::trie_iterator_state_t<Key, Value>;

    public:
        using element = trie_element<Key, Value>;
        using range = trie_range<Key, Value>;
        using const_range = const_trie_range<Key, Value>;
        using insert_result = trie_insert_result<Key, Value>;
        using match_result = trie_match_result<Key, Value>;

        using key_type = Key;
        using mapped_type = Value;
        using value_type = element;
        using key_compare = Compare;
        using key_element_type = typename Key::value_type;

        using reference = value_type &;
        using const_reference = value_type const &;
        using iterator = trie_iterator<key_type, mapped_type>;
        using const_iterator = const_trie_iterator<key_type, mapped_type>;
        using reverse_iterator = reverse_trie_iterator<key_type, mapped_type>;
        using const_reverse_iterator =
            const_reverse_trie_iterator<key_type, mapped_type>;
        using size_type = std::ptrdiff_t;
        using difference_type = std::ptrdiff_t;

        trie() : size_(0) {}

        trie(Compare const & comp) : comp_(comp), size_(0) {}

        template<typename Iter>
        trie(Iter first, Iter last, Compare const & comp = Compare()) :
            comp_(comp),
            size_(0)
        {
            insert(first, last);
        }
        template<typename Range>
        explicit trie(Range r, Compare const & comp = Compare()) :
            comp_(comp),
            size_(0)
        {
            using std::begin;
            using std::end;
            insert(begin(r), end(r));
        }
        trie(std::initializer_list<value_type> il) : size_(0) { insert(il); }

        trie & operator=(std::initializer_list<value_type> il)
        {
            clear();
            for (auto const & x : il) {
                insert(x);
            }
            return *this;
        }

        bool empty() const noexcept { return size_ == 0; }
        size_type size() const noexcept { return size_; }
        size_type max_size() const noexcept { return PTRDIFF_MAX; }

        const_iterator begin() const noexcept
        {
            iter_state_t state{&root_, 0};
            if (size_) {
                while (!state.parent_->min_value()) {
                    state.parent_ = state.parent_->min_child();
                }
            }
            return const_iterator(state);
        }
        const_iterator end() const noexcept
        {
            iter_state_t state{&root_, 0};
            if (size_) {
                node_t const * node = nullptr;
                while ((node = to_node(state))) {
                    state.parent_ = node;
                    state.index_ = state.parent_->size() - 1;
                }
                state.parent_ = state.parent_->parent();
                state.index_ = state.parent_->size();
            }
            return const_iterator(state);
        }
        const_iterator cbegin() const noexcept { return begin(); }
        const_iterator cend() const noexcept { return end(); }

        const_reverse_iterator rbegin() const noexcept
        {
            return const_reverse_iterator{end()};
        }
        const_reverse_iterator rend() const noexcept
        {
            return const_reverse_iterator{begin()};
        }
        const_reverse_iterator crbegin() const noexcept { return rbegin(); }
        const_reverse_iterator crend() const noexcept { return rend(); }

        // TODO: Figure out the right way to do this.
#define BOOST_TRIE_C_STR_OVERLOAD(rtype, func, quals)                          \
    rtype func(char const * chars) quals                                       \
    {                                                                          \
        static_assert(                                                         \
            std::is_same<key_element_type, char>::value,                       \
            "Only well-formed when Key::value_type is char.");                 \
        return func(text::string_view(chars));                                 \
    }

        template<typename KeyRange>
        bool contains(KeyRange const & key) const noexcept
        {
            return find(key) != end();
        }

        BOOST_TRIE_C_STR_OVERLOAD(bool, contains, const noexcept)

        template<typename KeyRange>
        const_iterator find(KeyRange const & key) const noexcept
        {
            using std::begin;
            using std::end;
            auto first = begin(key);
            auto const last = end(key);
            auto match = longest_match_impl(first, last);
            if (first == last && match.result_.match) {
                return const_iterator(iter_state_t{match.result_.node->parent(),
                                                   match.index_within_parent_});
            }
            return this->end();
        }

        BOOST_TRIE_C_STR_OVERLOAD(const_iterator, find, const noexcept)

        template<typename KeyRange>
        const_iterator lower_bound(KeyRange const & key) const noexcept
        {
            return bound_impl<true>(key);
        }

        BOOST_TRIE_C_STR_OVERLOAD(const_iterator, lower_bound, const noexcept)

        template<typename KeyRange>
        const_iterator upper_bound(KeyRange const & key) const noexcept
        {
            return bound_impl<false>(key);
        }

        BOOST_TRIE_C_STR_OVERLOAD(const_iterator, upper_bound, const noexcept)

        template<typename KeyRange>
        const_range equal_range(KeyRange const & key) const noexcept
        {
            return {lower_bound(key), upper_bound(key)};
        }

        BOOST_TRIE_C_STR_OVERLOAD(const_range, equal_range, const noexcept)

        template<typename KeyIter>
        match_result longest_match(KeyIter first, KeyIter last) const noexcept
        {
            return longest_match_impl(first, last).result_;
        }

        template<typename KeyRange>
        match_result longest_match(KeyRange const & key) const noexcept
        {
            using std::begin;
            using std::end;
            return longest_match(begin(key), end(key));
        }

        BOOST_TRIE_C_STR_OVERLOAD(match_result, longest_match, const noexcept)

        template<typename KeyElementT>
        match_result extend_match(match_result prev, KeyElementT e) const
            noexcept
        {
            auto e_ptr = &e;
            return extend_match_impl(priv_match_result{prev}, e_ptr, e_ptr + 1)
                .result_;
        }

        template<typename KeyIter>
        match_result
        extend_match(match_result prev, KeyIter first, KeyIter last) const
            noexcept
        {
            return extend_match_impl(priv_match_result{prev}, first, last)
                .result_;
        }

        template<typename KeyRange>
        optional<mapped_type> operator[](KeyRange const & key) const noexcept
        {
            auto it = find(key);
            if (it == end())
                return {};
            return it->value;
        }

        BOOST_TRIE_C_STR_OVERLOAD(
            optional<mapped_type>, operator[], const noexcept)

        iterator begin() noexcept { return iterator(const_this()->begin()); }
        iterator end() noexcept { return iterator(const_this()->end()); }
        iterator cbegin() noexcept { return begin(); }
        iterator cend() noexcept { return end(); }

        reverse_iterator rbegin() noexcept { return reverse_iterator{end()}; }
        reverse_iterator rend() noexcept { return reverse_iterator{begin()}; }
        reverse_iterator crbegin() noexcept { return rbegin(); }
        reverse_iterator crend() noexcept { return rend(); }

        void clear() noexcept
        {
            root_ = node_t();
            size_ = 0;
        }

        template<typename KeyRange>
        iterator find(KeyRange const & key) noexcept
        {
            return iterator(const_this()->find(key));
        }

        BOOST_TRIE_C_STR_OVERLOAD(iterator, find, noexcept)

        template<typename KeyRange>
        iterator lower_bound(KeyRange const & key) noexcept
        {
            return iterator(const_this()->lower_bound(key));
        }

        BOOST_TRIE_C_STR_OVERLOAD(iterator, lower_bound, noexcept)

        template<typename KeyRange>
        iterator upper_bound(KeyRange const & key) noexcept
        {
            return iterator(const_this()->upper_bound(key));
        }

        BOOST_TRIE_C_STR_OVERLOAD(iterator, upper_bound, noexcept)

        template<typename KeyRange>
        range equal_range(KeyRange const & key) noexcept
        {
            return {lower_bound(key), upper_bound(key)};
        }

        BOOST_TRIE_C_STR_OVERLOAD(range, equal_range, noexcept)

        template<typename KeyRange>
        optional<mapped_type &> operator[](KeyRange const & key) noexcept
        {
            auto it = find(key);
            if (it == end())
                return {};
            return it->value;
        }

        BOOST_TRIE_C_STR_OVERLOAD(optional<mapped_type &>, operator[], noexcept)

        template<typename KeyIter>
        insert_result insert(KeyIter first, KeyIter last, Value value)
        {
            if (empty()) {
                std::unique_ptr<node_t> new_node(new node_t(&root_));
                root_.insert(std::move(new_node));
            }

            auto const initial_first = first;
            auto match = longest_match_impl(first, last);
            if (first == last && match.result_.match) {
                return {iterator(iter_state_t{match.result_.node->parent(),
                                              match.index_within_parent_}),
                        false};
            }
            auto node = create_children(
                const_cast<node_t *>(match.result_.node), first, last);
            node->value() =
                element{key_type{initial_first, last}, std::move(value)};
            ++size_;
            return {iterator(iter_state_t{node->parent(), 0}), true};
        }

        template<typename KeyRange>
        insert_result insert(KeyRange const & key, Value value)
        {
            using std::begin;
            using std::end;
            return insert(begin(key), end(key), std::move(value));
        }

        // TODO: Must be treated the same as the macro used elsewhere.
        insert_result insert(char const * chars, Value value)
        {
            static_assert(
                std::is_same<key_element_type, char>::value,
                "Only well-formed when Key::value_type is char.");
            return insert(text::string_view(chars), std::move(value));
        }

        insert_result insert(element e)
        {
            using std::begin;
            using std::end;
            return insert(begin(e.key), end(e.key), std::move(e.value));
        }
        template<typename Iter>
        void insert(Iter first, Iter last)
        {
            for (; first != last; ++first) {
                insert(first->key, first->value);
            }
        }
        template<typename Range>
        insert_result insert(Range const & r)
        {
            using std::begin;
            using std::end;
            return insert(begin(r), end(r));
        }

        void insert(std::initializer_list<value_type> il)
        {
            for (auto const & x : il) {
                insert(x);
            }
        }

        template<typename KeyRange>
        bool erase(KeyRange const & key) noexcept
        {
            auto it = find(key);
            if (it == end())
                return false;
            erase(it);
            return true;
        }

        BOOST_TRIE_C_STR_OVERLOAD(bool, erase, noexcept)

        iterator erase(iterator it)
        {
            auto state = it.it_.state_;

            --size_;

            auto node =
                const_cast<node_t *>(state.parent_->child(state.index_));
            if (!node->empty()) {
                // node has a value, but also children.  Remove the value and
                // find the next-iterator.
                node->value() = optional<trie_element<Key, Value>>();
                while (!node->value()) {
                    node = node->min_child();
                    return iterator(iter_state_t{node->parent(), 0});
                }
            }

            // node has a value, *and* no children.  Remove it and all its
            // singular predecessors.
            const_cast<node_t *>(state.parent_)->erase(state.index_);
            while (state.parent_->parent() != state.parent_ &&
                   state.parent_->empty() && !state.parent_->value()) {
                state = parent_state(state);
                const_cast<node_t *>(state.parent_)->erase(state.index_);
            }

            auto retval = iterator(state);
            ++retval;

            return retval;
        }
        iterator erase(iterator first, iterator last)
        {
            iterator retval = first;
            while (last-- > first) {
                retval = erase(last);
            }
            return retval;
        }

        void swap(trie & other)
        {
            root_.swap(other.root_);
            std::swap(size_, other.size_);
            std::swap(comp_, other.comp_);
        }

        friend bool operator==(trie const & lhs, trie const & rhs)
        {
            return lhs.size() == rhs.size() &&
                   std::equal(lhs.begin(), lhs.end(), rhs.begin());
        }
        friend bool operator!=(trie const & lhs, trie const & rhs)
        {
            return !(lhs == rhs);
        }

    private:
        trie const * const_this() { return const_cast<trie const *>(this); }

        struct priv_match_result
        {
            match_result result_;
            std::size_t index_within_parent_;
        };

        template<typename KeyIter>
        priv_match_result
        longest_match_impl(KeyIter & first, KeyIter last) const noexcept
        {
            return extend_match_impl(
                priv_match_result{match_result{&root_, 0}}, first, last);
        }

        template<typename KeyIter>
        priv_match_result extend_match_impl(
            priv_match_result prev, KeyIter & first, KeyIter last) const
            noexcept
        {
            if (prev.result_.node == &root_) {
                if (root_.empty())
                    return prev;
                prev.result_.node = root_.child(0);
            }

            if (first == last) {
                prev.result_.match = !!prev.result_.node->value();
                return prev;
            }

            node_t const * node = prev.result_.node;
            size_type size = prev.result_.size;
            std::size_t parent_index = 0;
            while (first != last) {
                auto const it = node->find(*first, comp_);
                if (it == node->end())
                    break;
                ++first;
                ++size;
                parent_index = it - node->begin();
                node = it->get();
            }

            return {match_result{node, size, !!node->value()}, parent_index};
        }

        template<typename KeyIter>
        node_t * create_children(node_t * node, KeyIter first, KeyIter last)
        {
            auto retval = node;
            for (; first != last; ++first) {
                std::unique_ptr<node_t> new_node(new node_t(retval));
                retval =
                    retval->insert(*first, comp_, std::move(new_node))->get();
            }
            return retval;
        }

        template<bool LowerBound, typename KeyRange>
        const_iterator bound_impl(KeyRange const & key) const noexcept
        {
            using std::begin;
            using std::end;
            auto first = begin(key);
            auto const last = end(key);
            auto match = longest_match_impl(first, last);
            if (first == last && match.result_.match) {
                auto retval = const_iterator(iter_state_t{
                    match.result_.node->parent(), match.index_within_parent_});
                if (!LowerBound)
                    ++retval;
                return retval;
            }

            auto node = match.result_.node;
            if (node->before_child_subtree(*first)) {
                // If the next element of the key would be before this node's
                // children, use the successor of this node; let
                // const_iterator::operator++() figure out for us which node
                // that is.
                return ++const_iterator(iter_state_t{
                    node->parent(), match.index_within_parent_});
            }

            auto const it = node->lower_bound(*first, comp_);
            if (it == node->end()) {
                // Find the max value in this subtree, and go one past that.
                do {
                    node = node->max_child();
                } while (!node->value());
                return ++const_iterator(
                    iter_state_t{node->parent(), node->parent()->size() - 1});
            }

            // Otherwise, find the min value within the child found above.
            std::size_t parent_index = it - node->begin();
            node = it->get();
            while (!node->value()) {
                node = node->min_child();
                parent_index = 0;
            }
            return const_iterator(iter_state_t{node->parent(), parent_index});
        }

        node_t root_;
        key_compare comp_;
        size_type size_;
    };

    template<typename Key, typename Value>
    struct const_trie_iterator
    {
        using value_type = trie_element<Key, Value>;
        using pointer = const value_type *;
        using reference = const value_type &;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

        const_trie_iterator() noexcept : state_{nullptr, 0} {}

        reference operator*() const noexcept
        {
            return state_.parent_->child_value(state_.index_);
        }

        pointer operator->() const noexcept { return &**this; }

        const_trie_iterator & operator++() noexcept
        {
            auto node = to_node(state_);
            if (node && !node->empty()) {
                state_.parent_ = node;
                state_.index_ = 0;
            } else {
                // Try the next sibling node.
                ++state_.index_;
                auto const first_state = state_;
                while (state_.parent_->parent()->parent() &&
                       state_.parent_->size() <= state_.index_) {
                    state_ = parent_state(state_);
                    ++state_.index_;
                }

                // If we went all the way up, incrementing indices, and they
                // were all at size() for each node, the first increment above
                // must have taken us to the end; use that.
                if (!state_.parent_->parent()->parent() &&
                    state_.parent_->size() <= state_.index_) {
                    state_ = first_state;
                    return *this;
                }
            }

            node = state_.parent_->child(state_.index_);
            while (!node->value()) {
                auto i = 0u;
                node = node->child(i);
                state_ = state_t{node->parent(), i};
            }

            return *this;
        }
        const_trie_iterator operator++(int)noexcept
        {
            auto const retval = *this;
            ++*this;
            return retval;
        }
        const_trie_iterator & operator--() noexcept
        {
            // Decrement-from-end case.
            if (state_.index_ == state_.parent_->size()) {
                --state_.index_;
                return *this;
            }

            // Back up one node at a time until we find an ancestor with a
            // value or a previous sibling.
            while (state_.parent_->parent() && state_.index_ == 0) {
                state_ = parent_state(state_);
                if (state_.parent_->child(state_.index_)->value())
                    return *this;
            }

            // If we get found no value above, go down the maximum subtree of
            // the previous sibling.
            if (state_.index_)
                --state_.index_;
            auto node = state_.parent_->child(state_.index_);
            while (!node->value()) {
                auto i = node->size() - 1;
                node = node->child(i);
                state_ = state_t{node->parent(), i};
            }

            return *this;
        }
        const_trie_iterator operator--(int)noexcept
        {
            auto const retval = *this;
            --*this;
            return retval;
        }

        friend bool
        operator==(const_trie_iterator lhs, const_trie_iterator rhs) noexcept
        {
            return lhs.state_.parent_ == rhs.state_.parent_ &&
                   lhs.state_.index_ == rhs.state_.index_;
        }
        friend bool
        operator!=(const_trie_iterator lhs, const_trie_iterator rhs) noexcept
        {
            return !(lhs == rhs);
        }

    private:
        using state_t = detail::trie_iterator_state_t<Key, Value>;

        explicit const_trie_iterator(state_t state) : state_(state) {}

        state_t state_;

        template<typename KeyT, typename ValueT, typename Compare>
        friend struct trie;
        template<typename KeyT, typename ValueT>
        friend struct trie_iterator;
    };

    template<typename Key, typename Value>
    struct trie_iterator
    {
        using value_type = trie_element<Key, Value>;
        using pointer = value_type *;
        using reference = value_type &;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

        trie_iterator() {}

        reference operator*() const noexcept
        {
            return const_cast<reference>(*it_);
        }

        pointer operator->() const noexcept { return &**this; }

        trie_iterator & operator++() noexcept
        {
            ++it_;
            return *this;
        }
        trie_iterator operator++(int)noexcept
        {
            auto const retval = *this;
            ++*this;
            return retval;
        }
        trie_iterator & operator--() noexcept
        {
            --it_;
            return *this;
        }
        trie_iterator operator--(int)noexcept
        {
            auto const retval = *this;
            --*this;
            return retval;
        }

        friend bool operator==(trie_iterator lhs, trie_iterator rhs) noexcept
        {
            return lhs.it_ == rhs.it_;
        }
        friend bool operator!=(trie_iterator lhs, trie_iterator rhs) noexcept
        {
            return lhs.it_ != rhs.it_;
        }

    private:
        explicit trie_iterator(
            detail::trie_iterator_state_t<Key, Value> state) :
            it_(state)
        {}
        explicit trie_iterator(const_trie_iterator<Key, Value> it) : it_(it) {}

        const_trie_iterator<Key, Value> it_;

        template<typename KeyT, typename ValueT, typename Compare>
        friend struct trie;
    };

    template<typename Key, typename Value>
    struct reverse_trie_iterator
    {
        using value_type = trie_element<Key, Value>;
        using pointer = value_type *;
        using reference = value_type &;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

        reverse_trie_iterator() noexcept {}
        explicit reverse_trie_iterator(trie_iterator<Key, Value> it) noexcept :
            it_(it)
        {}

        reference operator*() const noexcept { return *std::prev(it_); }

        pointer operator->() const noexcept { return &**this; }

        reverse_trie_iterator & operator++() noexcept
        {
            --it_;
            return *this;
        }
        reverse_trie_iterator operator++(int)noexcept
        {
            auto const retval = *this;
            --*this;
            return retval;
        }
        reverse_trie_iterator & operator--() noexcept
        {
            ++it_;
            return *this;
        }
        reverse_trie_iterator operator--(int)noexcept
        {
            auto const retval = *this;
            ++*this;
            return retval;
        }

        trie_iterator<Key, Value> base() const noexcept { return it_; }

        friend bool operator==(
            reverse_trie_iterator lhs, reverse_trie_iterator rhs) noexcept
        {
            return lhs.it_ == rhs.it_;
        }
        friend bool operator!=(
            reverse_trie_iterator lhs, reverse_trie_iterator rhs) noexcept
        {
            return lhs.it_ != rhs.it_;
        }

    private:
        trie_iterator<Key, Value> it_;
    };

    template<typename Key, typename Value>
    struct const_reverse_trie_iterator
    {
        using value_type = trie_element<Key, Value>;
        using pointer = value_type const *;
        using reference = value_type const &;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

        const_reverse_trie_iterator() noexcept {}
        explicit const_reverse_trie_iterator(
            const_trie_iterator<Key, Value> it) noexcept :
            it_(it)
        {}
        explicit const_reverse_trie_iterator(
            reverse_trie_iterator<Key, Value> it) noexcept :
            it_(it.it_)
        {}

        reference operator*() const noexcept { return *std::prev(it_); }

        pointer operator->() const noexcept { return &**this; }

        const_reverse_trie_iterator & operator++() noexcept
        {
            --it_;
            return *this;
        }
        const_reverse_trie_iterator operator++(int)noexcept
        {
            auto const retval = *this;
            --*this;
            return retval;
        }
        const_reverse_trie_iterator & operator--() noexcept
        {
            ++it_;
            return *this;
        }
        const_reverse_trie_iterator operator--(int)noexcept
        {
            auto const retval = *this;
            ++*this;
            return retval;
        }

        const_trie_iterator<Key, Value> base() const noexcept { return it_; }

        friend bool operator==(
            const_reverse_trie_iterator lhs,
            const_reverse_trie_iterator rhs) noexcept
        {
            return lhs.it_ == rhs.it_;
        }
        friend bool operator!=(
            const_reverse_trie_iterator lhs,
            const_reverse_trie_iterator rhs) noexcept
        {
            return lhs.it_ != rhs.it_;
        }

    private:
        const_trie_iterator<Key, Value> it_;
    };

    namespace detail {

        template<typename Key, typename Value>
        struct trie_node_t
        {
            using children_t =
                std::vector<std::unique_ptr<trie_node_t<Key, Value>>>;
            using iterator = typename children_t::iterator;
            using const_iterator = typename children_t::const_iterator;
            using key_element = typename Key::value_type;

            trie_node_t() : parent_(nullptr) {}
            trie_node_t(trie_node_t * parent) : parent_(parent) {}
            trie_node_t(trie_node_t const & other) :
                keys_(other.keys_),
                value_(other.value_),
                parent_(other.parent_)
            {
                children_.reserve(other.children_.size());
                for (auto const & node : other.children_) {
                    std::unique_ptr<trie_node_t> new_node(
                        new trie_node_t(*node));
                    children_.push_back(std::move(new_node));
                }
            }
            trie_node_t(trie_node_t && other) : parent_(nullptr)
            {
                swap(other);
            }
            trie_node_t & operator=(trie_node_t const & rhs)
            {
                assert(
                    parent_ == nullptr &&
                    "Assignment of trie_node_ts are defined only for the root "
                    "node.");
                trie_node_t temp(rhs);
                temp.swap(*this);
                return *this;
            }
            trie_node_t & operator=(trie_node_t && rhs)
            {
                assert(
                    parent_ == nullptr &&
                    "Move assignments of trie_node_ts are defined only for the "
                    "root node.");
                trie_node_t temp(std::move(rhs));
                temp.swap(*this);
                return *this;
            }

            optional<trie_element<Key, Value>> const & value() const noexcept
            {
                return value_;
            }

            trie_element<Key, Value> & child_value(std::size_t i) const
            {
                return *children_[i]->value_;
            }

            trie_node_t * parent() const noexcept { return parent_; }
            trie_node_t * min_child() const noexcept
            {
                return children_.front().get();
            }
            trie_node_t * max_child() const noexcept
            {
                return children_.back().get();
            }

            bool empty() const noexcept { return children_.size() == 0; }
            std::size_t size() const noexcept { return children_.size(); }

            bool min_value() const noexcept
            {
                return !!children_.front()->value_;
            }
            bool max_value() const noexcept
            {
                return !!children_.back()->value_;
            }

            const_iterator begin() const noexcept { return children_.begin(); }
            const_iterator end() const noexcept { return children_.end(); }

            bool before_child_subtree(key_element const & e) const noexcept
            {
                return keys_.empty() || e < keys_.front();
            }

            template<typename Compare>
            const_iterator
            lower_bound(key_element const & e, Compare const & comp) const
                noexcept
            {
                auto const it = std::lower_bound(keys_.begin(), keys_.end(), e);
                return children_.begin() + (it - keys_.begin());
            }
            template<typename Compare>
            const_iterator
            find(key_element const & e, Compare const & comp) const noexcept
            {
                auto const it = lower_bound(e, comp);
                auto const end_ = end();
                if (it != end_ && comp(e, key(it)))
                    return end_;
                return it;
            }

            template<typename Compare>
            trie_node_t const *
            child(key_element const & e, Compare const & comp) const noexcept
            {
                auto const it = find(e, comp);
                if (it == children_.end())
                    return nullptr;
                return it->get();
            }
            trie_node_t const * child(std::size_t i) const noexcept
            {
                return children_[i].get();
            }

            void swap(trie_node_t & other)
            {
                assert(
                    parent_ == nullptr &&
                    "Swaps of trie_node_ts are defined only for the root "
                    "node.");
                keys_.swap(other.keys_);
                children_.swap(other.children_);
                value_.swap(other.value_);
                for (auto const & node : children_) {
                    node->parent_ = this;
                }
                for (auto const & node : other.children_) {
                    node->parent_ = &other;
                }
            }

            optional<trie_element<Key, Value>> & value() noexcept
            {
                return value_;
            }

            iterator begin() noexcept { return children_.begin(); }
            iterator end() noexcept { return children_.end(); }

            template<typename Compare>
            iterator insert(
                key_element const & e,
                Compare const & comp,
                std::unique_ptr<trie_node_t> && child)
            {
                auto it = std::lower_bound(keys_.begin(), keys_.end(), e);
                it = keys_.insert(it, e);
                auto child_it = children_.begin() + (it - keys_.begin());
                return children_.insert(child_it, std::move(child));
            }
            iterator insert(std::unique_ptr<trie_node_t> && child)
            {
                assert(empty());
                return children_.insert(children_.begin(), std::move(child));
            }
            void erase(std::size_t i) noexcept
            {
                keys_.erase(keys_.begin() + i);
                children_.erase(children_.begin() + i);
            }

            template<typename Compare>
            iterator
            lower_bound(key_element const & e, Compare const & comp) noexcept
            {
                auto const it = const_this()->lower_bound(e, comp);
                return children_.begin() +
                       (it - const_iterator(children_.begin()));
            }
            template<typename Compare>
            iterator find(key_element const & e, Compare const & comp) noexcept
            {
                auto const it = const_this()->find(e, comp);
                return children_.begin() +
                       (it - const_iterator(children_.begin()));
            }

            template<typename Compare>
            trie_node_t *
            child(key_element const & e, Compare const & comp) noexcept
            {
                return const_cast<trie_node_t *>(const_this()->child(e, comp));
            }
            trie_node_t * child(std::size_t i) noexcept
            {
                return const_cast<trie_node_t *>(const_this()->child(i));
            }

        private:
            trie_node_t const * const_this()
            {
                return const_cast<trie_node_t const *>(this);
            }
            key_element const & key(const_iterator it) const
            {
                return keys_[it - children_.begin()];
            }

            std::vector<key_element> keys_;
            children_t children_;
            optional<trie_element<Key, Value>> value_;
            trie_node_t * parent_;
        };
    }

}}

#endif
