#ifndef BOOST_TEXT_DETAIL_ROPE_ITERATOR_HPP
#define BOOST_TEXT_DETAIL_ROPE_ITERATOR_HPP

#include <iterator>


namespace boost { namespace text { namespace detail {

    struct const_rope_iterator
    {
        using value_type = char const;
        using difference_type = std::ptrdiff_t;
        using pointer = char const *;
        using reference = char const;
        using iterator_category = std::random_access_iterator_tag;

        const_rope_iterator () noexcept :
            rope_ (nullptr),
            n_ (-1),
            leaf_ (nullptr),
            leaf_start_ (-1)
        {}

        const_rope_iterator (rope const & r, difference_type n) noexcept :
            rope_ (&r),
            n_ (n),
            leaf_ (nullptr),
            leaf_start_ (0)
        {}

        reference operator* () const noexcept
        {
            if (leaf_) {
                return deref();
            } else {
                found_char found;
                find_char(rope_->ptr_, n_, found);
                leaf_ = found.leaf_.leaf_->as_leaf();
                leaf_start_ = n_ - found.leaf_.offset_;
                return found.c_;
            }
        }

        value_type operator[] (difference_type n) const noexcept
        {
            auto it = *this;
            if (0 <= n)
                it += n;
            else
                it -= -n;
            return *it;
        }

        const_rope_iterator & operator++ () noexcept
        {
            ++n_;
            if (leaf_ && n_ == leaf_start_ + leaf_->size())
                leaf_ = nullptr;
            return *this;
        }
        const_rope_iterator operator++ (int) noexcept
        {
            const_rope_iterator retval = *this;
            ++*this;
            return retval;
        }
        const_rope_iterator & operator+= (difference_type n) noexcept
        {
            n_ += n;
            leaf_ = nullptr;
            return *this;
        }

        const_rope_iterator & operator-- () noexcept
        {
            if (leaf_ && n_ == leaf_start_)
                leaf_ = nullptr;
            --n_;
            return *this;
        }
        const_rope_iterator operator-- (int) noexcept
        {
            const_rope_iterator retval = *this;
            --*this;
            return retval;
        }
        const_rope_iterator & operator-= (difference_type n) noexcept
        {
            n_ -= n;
            leaf_ = nullptr;
            return *this;
        }

        friend bool operator== (const_rope_iterator lhs, const_rope_iterator rhs) noexcept
        { return lhs.rope_ == rhs.rope_ && lhs.n_ == rhs.n_; }
        friend bool operator!= (const_rope_iterator lhs, const_rope_iterator rhs) noexcept
        { return !(lhs == rhs); }
        // TODO: Document wonky behavior of the inequalities when rhs.{frst,last}_ != rhs.{first,last}_.
        friend bool operator< (const_rope_iterator lhs, const_rope_iterator rhs) noexcept
        { return lhs.rope_ == rhs.rope_ && lhs.n_ < rhs.n_; }
        friend bool operator<= (const_rope_iterator lhs, const_rope_iterator rhs) noexcept
        { return lhs == rhs || lhs < rhs; }
        friend bool operator> (const_rope_iterator lhs, const_rope_iterator rhs) noexcept
        { return rhs < lhs; }
        friend bool operator>= (const_rope_iterator lhs, const_rope_iterator rhs) noexcept
        { return rhs <= lhs; }

        friend const_rope_iterator operator+ (const_rope_iterator lhs, difference_type rhs) noexcept
        { return lhs += rhs; }
        friend const_rope_iterator operator+ (difference_type lhs, const_rope_iterator rhs) noexcept
        { return rhs += lhs; }
        friend const_rope_iterator operator- (const_rope_iterator lhs, difference_type rhs) noexcept
        { return lhs -= rhs; }
        friend const_rope_iterator operator- (difference_type lhs, const_rope_iterator rhs) noexcept
        { return rhs -= lhs; }
        friend difference_type operator- (const_rope_iterator lhs, const_rope_iterator rhs) noexcept
        {
            // TODO: Document this precondition!
            assert(lhs.rope_ == rhs.rope_);
            return lhs.n_ - rhs.n_;
        }

    private:
        char deref () const
        {
            switch (leaf_->which_) {
            case node_t::which::t: {
                text const * t = static_cast<text *>(leaf_->buf_ptr_);
                return *(t->begin() + (n_ - leaf_start_));
            }
            case node_t::which::tv: {
                text_view const * tv = static_cast<text_view *>(leaf_->buf_ptr_);
                return *(tv->begin() + (n_ - leaf_start_));
            }
            case node_t::which::rtv: {
                repeated_text_view const * rtv = static_cast<repeated_text_view *>(leaf_->buf_ptr_);
                return *(rtv->begin() + (n_ - leaf_start_));
            }
            case node_t::which::ref: {
                detail::reference const * ref = static_cast<detail::reference *>(leaf_->buf_ptr_);
                return *(ref->ref_.begin() + (n_ - leaf_start_));
            }
            default: assert(!"unhandled rope node case"); break;
            }
            return '\0'; // This should never execute.
        }

        rope const * rope_;
        difference_type n_;
        mutable leaf_node_t const * leaf_;
        mutable difference_type leaf_start_;
    };

    struct const_reverse_rope_iterator
    {
        using value_type = char const;
        using difference_type = std::ptrdiff_t;
        using pointer = char const *;
        using reference = char const;
        using iterator_category = std::random_access_iterator_tag;

        const_reverse_rope_iterator () noexcept : base_ () {}
        explicit const_reverse_rope_iterator (const_rope_iterator it) noexcept : base_ (it) {}

        const_rope_iterator base () const { return base_ + 1; }

        reference operator* () const noexcept { return *base_; }
        value_type operator[] (difference_type n) const noexcept { return base_[-n]; }

        const_reverse_rope_iterator & operator++ () noexcept { --base_; return *this; }
        const_reverse_rope_iterator operator++ (int) noexcept
        {
            const_reverse_rope_iterator retval = *this;
            --base_;
            return retval;
        }
        const_reverse_rope_iterator & operator+= (difference_type n) noexcept { base_ -= n; return *this; }

        const_reverse_rope_iterator & operator-- () noexcept { ++base_; return *this; }
        const_reverse_rope_iterator operator-- (int) noexcept
        {
            const_reverse_rope_iterator retval = *this;
            ++base_;
            return retval;
        }
        const_reverse_rope_iterator & operator-= (difference_type n) noexcept { base_ += n; return *this; }

        friend bool operator== (const_reverse_rope_iterator lhs, const_reverse_rope_iterator rhs) noexcept
        { return lhs.base_ == rhs.base_; }
        friend bool operator!= (const_reverse_rope_iterator lhs, const_reverse_rope_iterator rhs) noexcept
        { return !(lhs == rhs); }
        friend bool operator< (const_reverse_rope_iterator lhs, const_reverse_rope_iterator rhs) noexcept
        { return rhs.base_ < lhs.base_; }
        friend bool operator<= (const_reverse_rope_iterator lhs, const_reverse_rope_iterator rhs) noexcept
        { return rhs.base_ <= lhs.base_; }
        friend bool operator> (const_reverse_rope_iterator lhs, const_reverse_rope_iterator rhs) noexcept
        { return rhs.base_ > lhs.base_; }
        friend bool operator>= (const_reverse_rope_iterator lhs, const_reverse_rope_iterator rhs) noexcept
        { return rhs.base_ >= lhs.base_; }

        friend const_reverse_rope_iterator operator+ (const_reverse_rope_iterator lhs, difference_type rhs) noexcept
        { return lhs += rhs; }
        friend const_reverse_rope_iterator operator+ (difference_type lhs, const_reverse_rope_iterator rhs) noexcept
        { return rhs += lhs; }
        friend const_reverse_rope_iterator operator- (const_reverse_rope_iterator lhs, difference_type rhs) noexcept
        { return lhs -= rhs; }
        friend const_reverse_rope_iterator operator- (difference_type lhs, const_reverse_rope_iterator rhs) noexcept
        { return rhs -= lhs; }
        friend difference_type operator- (const_reverse_rope_iterator lhs, const_reverse_rope_iterator rhs) noexcept
        { return rhs.base_ - lhs.base_; }

    private:
        const_rope_iterator base_;
    };

} } }

#endif