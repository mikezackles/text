
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
    if (!exists(boost::filesystem::path("ml_standard.table"))) {
        string const table_str(data::ml::standard_collation_tailoring());
        collation_table table = tailored_collation_table(
            table_str,
            "ml::standard_collation_tailoring()", error, warning);
        save_table(table, "ml_standard.table.0");
        boost::filesystem::rename("ml_standard.table.0", "ml_standard.table");
    }
    return load_table("ml_standard.table");
}
collation_table const & table()
{
    static collation_table retval = make_save_load_table();
    return retval;
}
TEST(tailoring, ml_standard_000_001)
{
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x0d03);
    auto const rel = std::vector<uint32_t>(1, 0x0d3d);
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
    auto const res = std::vector<uint32_t>(1, 0x0d4c);
    auto const rel = std::vector<uint32_t>(1, 0x0d57);
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
    auto const res = std::vector<uint32_t>{0x0d15, 0x0d4d};
    auto const rel = std::vector<uint32_t>{0x0d15, 0x0d4d, 0x200d};
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
    auto const res = std::vector<uint32_t>{0x0d15, 0x0d4d, 0x200d};
    auto const rel = std::vector<uint32_t>(1, 0x0d7f);
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
    auto const res = std::vector<uint32_t>{0x0d23, 0x0d4d};
    auto const rel = std::vector<uint32_t>{0x0d23, 0x0d4d, 0x200d};
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
    auto const res = std::vector<uint32_t>{0x0d23, 0x0d4d, 0x200d};
    auto const rel = std::vector<uint32_t>(1, 0x0d7a);
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
    auto const res = std::vector<uint32_t>{0x0d28, 0x0d4d};
    auto const rel = std::vector<uint32_t>{0x0d28, 0x0d4d, 0x200d};
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
    auto const res = std::vector<uint32_t>{0x0d28, 0x0d4d, 0x200d};
    auto const rel = std::vector<uint32_t>(1, 0x0d7b);
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
    auto const res = std::vector<uint32_t>{0x0d30, 0x0d4d};
    auto const rel = std::vector<uint32_t>{0x0d30, 0x0d4d, 0x200d};
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
    auto const res = std::vector<uint32_t>{0x0d30, 0x0d4d, 0x200d};
    auto const rel = std::vector<uint32_t>(1, 0x0d7c);
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
    auto const res = std::vector<uint32_t>{0x0d32, 0x0d4d};
    auto const rel = std::vector<uint32_t>{0x0d32, 0x0d4d, 0x200d};
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
    auto const res = std::vector<uint32_t>{0x0d32, 0x0d4d, 0x200d};
    auto const rel = std::vector<uint32_t>(1, 0x0d7d);
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
    auto const res = std::vector<uint32_t>{0x0d33, 0x0d4d};
    auto const rel = std::vector<uint32_t>{0x0d33, 0x0d4d, 0x200d};
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
    auto const res = std::vector<uint32_t>{0x0d33, 0x0d4d, 0x200d};
    auto const rel = std::vector<uint32_t>(1, 0x0d7e);
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
    auto const res = std::vector<uint32_t>{0x0d2e, 0x0d4d};
    auto const rel = std::vector<uint32_t>(1, 0x0d02);
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
    auto const res = std::vector<uint32_t>{0x0d28, 0x0d4d};
    auto const rel = std::vector<uint32_t>{0x0d7b, 0x0d4d};
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
}
