#ifndef BOOST_TEXT_TABLE_SERIALIZATION_HPP
#define BOOST_TEXT_TABLE_SERIALIZATION_HPP

#include <boost/text/collation_table.hpp>
#include <boost/text/detail/serialization.hpp>


namespace boost { namespace text {

    /** TODO */
    template<typename CharIter>
    CharIter write_table(collation_table const & table, CharIter out) noexcept;

    /** TODO */
    template<typename CharIter>
    struct read_table_result
    {
        operator collation_table() && { return table; }

        collation_table table;
        CharIter out;
    };

    /** TODO */
    template<typename CharIter>
    read_table_result<CharIter> read_table(CharIter it);

    namespace detail {

        template<typename CharIter, typename T>
        void read_bytes(CharIter & it, T & x, iterator_tag_t)
        {
            char * ptr = reinterpret_cast<char *>(&x);
            for (std::ptrdiff_t i = 0, end = sizeof(T); i < end;
                 ++i, ++ptr, ++it) {
                *ptr = *it;
            }
        }

        template<typename T, typename CharIter>
        void write_bytes(T const & x, CharIter & out, iterator_tag_t)
        {
            char const * const ptr = reinterpret_cast<char const *>(&x);
            out = std::copy_n(ptr, sizeof(T), out);
        }
    }

    template<typename CharIter>
    CharIter
    write_table(collation_table const & table_proper, CharIter out) noexcept
    {
        auto const & table = *table_proper.data_;

        detail::header_t header(table);

        detail::write_bytes(header, out);

        detail::write_collation_elements(
            table.collation_element_vec_, table.collation_elements_, out);

        detail::write_nonsimple_reorders(table.nonsimple_reorders_, out);

        detail::write_simple_reorders(table.simple_reorders_, out);

        detail::write_trie(table.trie_, out);

        return out;
    }

    template<typename CharIter>
    read_table_result<CharIter> read_table(CharIter it)
    {
        collation_table retval;

        auto & table = *retval.data_;

        detail::header_t header;
        detail::read_bytes(it, header);

        detail::read_collation_elements(
            it,
            table.collation_element_vec_,
            table.collation_elements_,
            header.collation_elements_.value());

        detail::read_nonsimple_reorders(
            it, table.nonsimple_reorders_, header.nonsimple_reorders_.value());

        detail::read_simple_reorders(
            it, table.simple_reorders_, header.simple_reorders_.value());

        detail::header_to_table(header, table);

        detail::read_trie(it, table.trie_, header.trie_.value());

        return read_table_result<CharIter>{std::move(retval), it};
    }

}}

#endif