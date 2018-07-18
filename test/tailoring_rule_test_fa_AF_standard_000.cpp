
// Warning! This file is autogenerated.
#include <boost/text/collation_table.hpp>
#include <boost/text/collate.hpp>
#include <boost/text/save_load_table.hpp>
#include <boost/text/data/all.hpp>

#include <boost/filesystem.hpp>

#include <gtest/gtest.h>

using namespace boost::text;

auto const error = [](string const & s) { std::cout << s; };
auto const warning = [](string const & s) {};

collation_table make_save_load_table()
{
    if (!exists(boost::filesystem::path("fa_AF_standard.table"))) {
        string const table_str(data::fa_AF::standard_collation_tailoring());
        collation_table table = tailored_collation_table(
            table_str,
            "fa_AF::standard_collation_tailoring()", error, warning);
        save_table(table, "fa_AF_standard.table.0");
        boost::filesystem::rename("fa_AF_standard.table.0", "fa_AF_standard.table");
    }
    return load_table("fa_AF_standard.table");
}
collation_table const & table()
{
    static collation_table retval = make_save_load_table();
    return retval;
}
TEST(tailoring, fa_AF_standard_000_001)
{
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x064e);
    auto const rel = std::vector<uint32_t>(1, 0x0650);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x0650);
    auto const rel = std::vector<uint32_t>(1, 0x064f);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x064f);
    auto const rel = std::vector<uint32_t>(1, 0x064b);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x064b);
    auto const rel = std::vector<uint32_t>(1, 0x064d);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x064d);
    auto const rel = std::vector<uint32_t>(1, 0x064c);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x0627);
    auto const rel = std::vector<uint32_t>(1, 0x0623);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x0623);
    auto const rel = std::vector<uint32_t>(1, 0x0672);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x0672);
    auto const rel = std::vector<uint32_t>(1, 0x0671);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x0671);
    auto const rel = std::vector<uint32_t>(1, 0x0625);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x0625);
    auto const rel = std::vector<uint32_t>(1, 0x0673);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x0673);
    auto const rel = std::vector<uint32_t>(1, 0x0621);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        -1);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x062a);
    auto const rel = std::vector<uint32_t>(1, 0x067c);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        -1);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x067c);
    auto const rel = std::vector<uint32_t>(1, 0x0679);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x062c);
    auto const rel = std::vector<uint32_t>(1, 0x0681);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        -1);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x0681);
    auto const rel = std::vector<uint32_t>{0x062d, 0x0654};
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x0686);
    auto const rel = std::vector<uint32_t>(1, 0x0685);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        -1);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x062f);
    auto const rel = std::vector<uint32_t>(1, 0x0689);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        -1);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x0689);
    auto const rel = std::vector<uint32_t>(1, 0x0688);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x0631);
    auto const rel = std::vector<uint32_t>(1, 0x0693);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        -1);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x0693);
    auto const rel = std::vector<uint32_t>(1, 0x0691);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x0698);
    auto const rel = std::vector<uint32_t>(1, 0x0696);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        -1);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x06a9);
    auto const rel = std::vector<uint32_t>(1, 0x06aa);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x06aa);
    auto const rel = std::vector<uint32_t>(1, 0x0643);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x06ab);
    auto const rel = std::vector<uint32_t>(1, 0x06af);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x06bc);
    auto const rel = std::vector<uint32_t>(1, 0x06bb);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x0648);
    auto const rel = std::vector<uint32_t>(1, 0x0624);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x0624);
    auto const rel = std::vector<uint32_t>(1, 0x06c7);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x06c7);
    auto const rel = std::vector<uint32_t>(1, 0x06c9);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x0647);
    auto const rel = std::vector<uint32_t>(1, 0x06c0);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::tertiary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x06c0);
    auto const rel = std::vector<uint32_t>{0x0647, 0x0654};
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::tertiary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>{0x0647, 0x0654};
    auto const rel = std::vector<uint32_t>(1, 0x06d5);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x06d5);
    auto const rel = std::vector<uint32_t>(1, 0x06c1);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x06c1);
    auto const rel = std::vector<uint32_t>(1, 0x06be);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x06be);
    auto const rel = std::vector<uint32_t>(1, 0x0629);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x0629);
    auto const rel = std::vector<uint32_t>(1, 0x06c3);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
}

TEST(tailoring, fa_AF_standard_000_002)
{
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x06cc);
    auto const rel = std::vector<uint32_t>(1, 0x0649);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x0649);
    auto const rel = std::vector<uint32_t>(1, 0x06d2);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x06d2);
    auto const rel = std::vector<uint32_t>(1, 0x064a);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x064a);
    auto const rel = std::vector<uint32_t>(1, 0x06d0);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x06d0);
    auto const rel = std::vector<uint32_t>(1, 0x06cd);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x06cd);
    auto const rel = std::vector<uint32_t>{0x06cc, 0x0654};
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>{0x06cc, 0x0654};
    auto const rel = std::vector<uint32_t>{0x0649, 0x0654};
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::tertiary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>{0x0649, 0x0654};
    auto const rel = std::vector<uint32_t>(1, 0x0626);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::tertiary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x00a0);
    auto const rel = std::vector<uint32_t>(1, 0x200c);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x200c);
    auto const rel = std::vector<uint32_t>(1, 0x200d);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::secondary),
        -1);
    // equal to preceeding cps at next-lower strength
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        0);
    }
}
