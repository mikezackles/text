
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
    if (!exists(boost::filesystem::path("km_standard.table"))) {
        string const table_str(data::km::standard_collation_tailoring());
        collation_table table = tailored_collation_table(
            table_str,
            "km::standard_collation_tailoring()", error, warning);
        save_table(table, "km_standard.table.0");
        boost::filesystem::rename("km_standard.table.0", "km_standard.table");
    }
    return load_table("km_standard.table");
}
collation_table const & table()
{
    static collation_table retval = make_save_load_table();
    return retval;
}
TEST(tailoring, km_standard_000_001)
{
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0xfffb);
    auto const rel = std::vector<uint32_t>(1, 0x17b4);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::quaternary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x17b4);
    auto const rel = std::vector<uint32_t>(1, 0x17b5);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::quaternary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>{0x17d4, 0x179b, 0x17d4};
    auto const rel = std::vector<uint32_t>(1, 0x17d8);
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
    auto const res = std::vector<uint32_t>(1, 0x17c8);
    auto const rel = std::vector<uint32_t>(1, 0x17ce);
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
    auto const res = std::vector<uint32_t>(1, 0x17ce);
    auto const rel = std::vector<uint32_t>(1, 0x17cf);
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
    auto const res = std::vector<uint32_t>(1, 0x17cf);
    auto const rel = std::vector<uint32_t>(1, 0x17d1);
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
    auto const res = std::vector<uint32_t>(1, 0x17d1);
    auto const rel = std::vector<uint32_t>(1, 0x17d0);
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
    auto const res = std::vector<uint32_t>(1, 0x17d0);
    auto const rel = std::vector<uint32_t>(1, 0x17c8);
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
    auto const res = std::vector<uint32_t>(1, 0x17c8);
    auto const rel = std::vector<uint32_t>(1, 0x17dd);
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
    auto const res = std::vector<uint32_t>(1, 0x17dd);
    auto const rel = std::vector<uint32_t>(1, 0x17cb);
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
    auto const res = std::vector<uint32_t>(1, 0x17cb);
    auto const rel = std::vector<uint32_t>(1, 0x17c9);
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
    auto const res = std::vector<uint32_t>(1, 0x17c9);
    auto const rel = std::vector<uint32_t>(1, 0x17ca);
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
    auto const res = std::vector<uint32_t>(1, 0x17ca);
    auto const rel = std::vector<uint32_t>(1, 0x17cd);
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
    auto const res = std::vector<uint32_t>(1, 0x179a);
    auto const rel = std::vector<uint32_t>(1, 0x17ab);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        -1);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x17ab);
    auto const rel = std::vector<uint32_t>(1, 0x17ac);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        -1);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x179b);
    auto const rel = std::vector<uint32_t>(1, 0x17ad);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        -1);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x17ad);
    auto const rel = std::vector<uint32_t>(1, 0x17ae);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        -1);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1780};
    auto const rel = std::vector<uint32_t>{0x1780, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1781};
    auto const rel = std::vector<uint32_t>{0x1781, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1782};
    auto const rel = std::vector<uint32_t>{0x1782, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1783};
    auto const rel = std::vector<uint32_t>{0x1783, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1784};
    auto const rel = std::vector<uint32_t>{0x1784, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1785};
    auto const rel = std::vector<uint32_t>{0x1785, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1786};
    auto const rel = std::vector<uint32_t>{0x1786, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1787};
    auto const rel = std::vector<uint32_t>{0x1787, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1788};
    auto const rel = std::vector<uint32_t>{0x1788, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1789};
    auto const rel = std::vector<uint32_t>{0x1789, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x178a};
    auto const rel = std::vector<uint32_t>{0x178a, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x178b};
    auto const rel = std::vector<uint32_t>{0x178b, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x178c};
    auto const rel = std::vector<uint32_t>{0x178c, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x178d};
    auto const rel = std::vector<uint32_t>{0x178d, 0x17cc};
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

TEST(tailoring, km_standard_000_002)
{
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x178e};
    auto const rel = std::vector<uint32_t>{0x178e, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x178f};
    auto const rel = std::vector<uint32_t>{0x178f, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1790};
    auto const rel = std::vector<uint32_t>{0x1790, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1791};
    auto const rel = std::vector<uint32_t>{0x1791, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1792};
    auto const rel = std::vector<uint32_t>{0x1792, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1793};
    auto const rel = std::vector<uint32_t>{0x1793, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1794};
    auto const rel = std::vector<uint32_t>{0x1794, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1795};
    auto const rel = std::vector<uint32_t>{0x1795, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1796};
    auto const rel = std::vector<uint32_t>{0x1796, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1797};
    auto const rel = std::vector<uint32_t>{0x1797, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1798};
    auto const rel = std::vector<uint32_t>{0x1798, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x1799};
    auto const rel = std::vector<uint32_t>{0x1799, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x179a};
    auto const rel = std::vector<uint32_t>{0x179a, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x17ab};
    auto const rel = std::vector<uint32_t>{0x17ab, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x17ac};
    auto const rel = std::vector<uint32_t>{0x17ac, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x179b};
    auto const rel = std::vector<uint32_t>{0x179b, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x17ad};
    auto const rel = std::vector<uint32_t>{0x17ad, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x17ae};
    auto const rel = std::vector<uint32_t>{0x17ae, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x179c};
    auto const rel = std::vector<uint32_t>{0x179c, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x179d};
    auto const rel = std::vector<uint32_t>{0x179d, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x179e};
    auto const rel = std::vector<uint32_t>{0x179e, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x179f};
    auto const rel = std::vector<uint32_t>{0x179f, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x17a0};
    auto const rel = std::vector<uint32_t>{0x17a0, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x17a1};
    auto const rel = std::vector<uint32_t>{0x17a1, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x179a, 0x17d2, 0x17a2};
    auto const rel = std::vector<uint32_t>{0x17a2, 0x17cc};
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
    auto const res = std::vector<uint32_t>{0x17a2, 0x17cc};
    auto const rel = std::vector<uint32_t>{0x17a3, 0x17cc};
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::quaternary),
        0);
    }
}

TEST(tailoring, km_standard_000_003)
{
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x17a2);
    auto const rel = std::vector<uint32_t>(1, 0x17a3);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::quaternary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>{0x17a2, 0x17b6};
    auto const rel = std::vector<uint32_t>(1, 0x17a4);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::quaternary),
        0);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>{0x17a2, 0x17b7};
    auto const rel = std::vector<uint32_t>(1, 0x17a5);
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
    auto const res = std::vector<uint32_t>{0x17a2, 0x17b8};
    auto const rel = std::vector<uint32_t>(1, 0x17a6);
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
    auto const res = std::vector<uint32_t>{0x17a2, 0x17bb};
    auto const rel = std::vector<uint32_t>(1, 0x17a7);
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
    auto const res = std::vector<uint32_t>{0x17a2, 0x17bc};
    auto const rel = std::vector<uint32_t>(1, 0x17a9);
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
    auto const res = std::vector<uint32_t>{0x17a2, 0x17c2};
    auto const rel = std::vector<uint32_t>(1, 0x17af);
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
    auto const res = std::vector<uint32_t>{0x17a2, 0x17c3};
    auto const rel = std::vector<uint32_t>(1, 0x17b0);
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
    auto const res = std::vector<uint32_t>{0x17a2, 0x17c4};
    auto const rel = std::vector<uint32_t>(1, 0x17b1);
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
    auto const res = std::vector<uint32_t>{0x17a2, 0x17c5};
    auto const rel = std::vector<uint32_t>(1, 0x17b3);
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
    auto const res = std::vector<uint32_t>{0x17a7, 0x1780};
    auto const rel = std::vector<uint32_t>(1, 0x17a8);
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
    auto const res = std::vector<uint32_t>{0x17a9, 0x179c};
    auto const rel = std::vector<uint32_t>(1, 0x17aa);
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
    auto const res = std::vector<uint32_t>(1, 0x17b1);
    auto const rel = std::vector<uint32_t>(1, 0x17b2);
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
    auto const res = std::vector<uint32_t>(1, 0x17c5);
    auto const rel = std::vector<uint32_t>{0x17bb, 0x17c6};
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        -1);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>{0x17bb, 0x17c6};
    auto const rel = std::vector<uint32_t>(1, 0x17c6);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        -1);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x17c6);
    auto const rel = std::vector<uint32_t>{0x17b6, 0x17c6};
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        -1);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>{0x17b6, 0x17c6};
    auto const rel = std::vector<uint32_t>(1, 0x17c7);
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        -1);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>(1, 0x17c7);
    auto const rel = std::vector<uint32_t>{0x17b7, 0x17c7};
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        -1);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>{0x17b7, 0x17c7};
    auto const rel = std::vector<uint32_t>{0x17bb, 0x17c7};
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        -1);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>{0x17bb, 0x17c7};
    auto const rel = std::vector<uint32_t>{0x17c1, 0x17c7};
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        -1);
    }
    // greater than (or equal to, for =) preceeding cps
    {
    auto const res = std::vector<uint32_t>{0x17c1, 0x17c7};
    auto const rel = std::vector<uint32_t>{0x17c4, 0x17c7};
    EXPECT_EQ(collate(
        res.begin(), res.end(),
        rel.begin(), rel.end(),
        table(), collation_strength::primary),
        -1);
    }
}
