#!/usr/bin/env python
import lzw

cpp_file_form = decls = '''\
// Warning! This file is autogenerated.
#include <boost/text/{3}.hpp>
#include <boost/text/detail/break_prop_iter.hpp>

#include <boost/assert.hpp>

#include <algorithm>
#include <array>
#include <unordered_map>


namespace boost {{ namespace text {{ inline namespace v1 {{ namespace detail {{

std::array<{0}_interval, {1}> const & make_{0}_intervals()
{{
static std::array<{0}_interval, {1}> retval = {{{{
{2}
}}}};
return retval;
}}

std::unordered_map<uint32_t, {0}erty> make_{0}_map()
{{
constexpr std::array<unsigned char, {5}> compressed = {{{{
{4}
}}}};
std::unordered_map<uint32_t, {0}erty> retval;
container::small_vector<unsigned char, 256> buf;
std::copy(
    compressed.begin(),
    compressed.end(),
    lzw_to_break_prop_iter<{0}erty>(retval, buf));
BOOST_ASSERT(buf.empty());
BOOST_ASSERT(retval.size() == {6});
return retval;
}}

}}}}}}}}
'''

bidi_header_form = decls = '''\
// Warning! This file is autogenerated.
#ifndef BOOST_TEXT_DETAIL_BIDIRECTIONAL_HPP
#define BOOST_TEXT_DETAIL_BIDIRECTIONAL_HPP

#include <boost/text/bidirectional_fwd.hpp>

#include <algorithm>
#include <array>

#include <stdint.h>


namespace boost {{ namespace text {{ inline namespace v1 {{ namespace detail {{

enum class bidi_bracket_type {{
    open,
    close
}};

struct bidi_bracket_data
{{
    explicit operator bool() const {{ return cp_ != 0; }}

    uint32_t cp_;
    uint32_t paired_bracket_;
    bidi_bracket_type type_;
}};

inline bidi_bracket_data bidi_bracket(uint32_t cp) noexcept
{{
    static std::array<bidi_bracket_data, {1}> const brackets = {{{{
{0}
    }}}};

    auto const it = std::lower_bound(
        brackets.begin(), brackets.end(), bidi_bracket_data{{cp}},
        [](bidi_bracket_data lhs, bidi_bracket_data rhs){{
            return lhs.cp_ < rhs.cp_;
        }});
    if (it == brackets.end() || it->cp_ != cp)
        return bidi_bracket_data{{0}};
    return *it;
}}

struct bidi_mirroring_data
{{
    uint32_t cp_;
    int index_; // within bidi_mirroreds()
}};

inline int bidi_mirroring(uint32_t cp) noexcept
{{
    static std::array<bidi_mirroring_data, {3}> const mirrorings = {{{{
{2}
    }}}};

    auto const it = std::lower_bound(
        mirrorings.begin(), mirrorings.end(), bidi_mirroring_data{{cp}},
        [](bidi_mirroring_data lhs, bidi_mirroring_data rhs){{
            return lhs.cp_ < rhs.cp_;
        }});
    if (it == mirrorings.end() || it->cp_ != cp)
        return -1;
    return it->index_;
}}

inline std::array<uint32_t, {3}> const & bidi_mirroreds() noexcept
{{
    static std::array<uint32_t, {3}> const retval = {{{{
{4}
    }}}};
    return retval;
}}

}}}}}}}}

#endif
'''


def extract_extended_pictographic(filename):
    intervals = []
    lines = open(filename, 'r').readlines()
    for line in lines:
        line = line[:-1]
        if not line.startswith('#') and len(line) != 0:
            comment_start = line.find('#')
            comment = ''
            if comment_start != -1:
                comment = line[comment_start + 1:].strip()
                line = line[:comment_start]
            fields = map(lambda x: x.strip(), line.split(';'))
            prop = fields[1]
            if prop != 'Extended_Pictographic':
                continue
            code_points = fields[0]
            if '..' in code_points:
                cps = code_points.split('.')
                interval = (int(cps[0], 16), int(cps[2], 16) + 1, 'ExtPict')
            else:
                cp = int(code_points, 16)
                interval = (cp, cp + 1, 'ExtPict')
            intervals.append(interval)
    return intervals


def extract_break_properties(filename, prop_, prop_names, ext_pict_intervals):
    intervals = []
    for interval in ext_pict_intervals:
        intervals.append(interval)
    prop_enum = prop_ + 'erty'
    break_prop_lines = open(filename, 'r').readlines()
    for line in break_prop_lines:
        line = line[:-1]
        if not line.startswith('#') and len(line) != 0:
            comment_start = line.find('#')
            comment = ''
            if comment_start != -1:
                comment = line[comment_start + 1:].strip()
                line = line[:comment_start]
            fields = map(lambda x: x.strip(), line.split(';'))
            prop = fields[1]
            code_points = fields[0]
            if '..' in code_points:
                cps = code_points.split('.')
                interval = (int(cps[0], 16), int(cps[2], 16) + 1, prop)
            else:
                cp = int(code_points, 16)
                interval = (cp, cp + 1, prop)
            if 'line' not in prop_ or 'SG' not in interval[2]: # Skip surrogates.
                intervals.append(interval)

    intervals = sorted(intervals)
    intervals_list = ''
    intervals_map = []
    num_intervals = 0
    for interval in intervals:
        if 128 < interval[1] - interval[0]:
            num_intervals += 1
            intervals_list += '    {}_interval{{{}, {}, {}::{}}},\n'.format(
                prop_, hex(interval[0]), hex(interval[1]), prop_enum, interval[2]
            )
        else:
            for i in range(interval[0], interval[1]):
                intervals_map.append((i, prop_names[interval[2]]))
    return (intervals_list, num_intervals, intervals_map)


def extract_line_break_properties(filename, prop_, prop_names):
    # https://unicode.org/reports/tr14/#BreakingRules
    # LB1 defines this mapping as the first step of line breaking.  We're
    # doing it in data generation instead.
    # Resolved  Original    General_Category
    # AL        AI, SG, XX  Any
    # CM        SA          Only Mn or Mc
    # AL        SA          Any except Mn and Mc
    # NS        CJ          Any

    unicode_data_lines = open('UnicodeData.txt', 'r').readlines()
    gen_category = {} # code point -> General_Category
    for line in unicode_data_lines:
        tokens = line.split(';')
        gen_category[int(tokens[0], 16)] = tokens[2]

    intervals = []
    prop_enum = prop_ + 'erty'
    break_prop_lines = open(filename, 'r').readlines()
    for line in break_prop_lines:
        line = line[:-1]
        if not line.startswith('#') and len(line) != 0:
            comment_start = line.find('#')
            comment = ''
            if comment_start != -1:
                comment = line[comment_start + 1:].strip()
                line = line[:comment_start]
            fields = map(lambda x: x.strip(), line.split(';'))
            prop = fields[1]
            if prop == 'AI' or prop == 'SG' or prop == 'XX':
                prop = 'AL'
            if prop == 'CJ':
                prop = 'NS'
            code_points = fields[0]
            if '..' in code_points:
                cps = code_points.split('.')
                cps[0] = int(cps[0], 16)
                cps[2] = int(cps[2], 16)
                if prop == 'SA':
                    if gen_category[cps[0]] != gen_category[cps[2]]:
                        raise Exception('Oops!  Not all CPs in this range have the same General_Category.')
                    if gen_category[cps[0]] in ['Mn', 'Mc']:
                        prop = 'CM'
                    else:
                        prop = 'AL'
                interval = (cps[0], cps[2] + 1, prop)
            else:
                cp = int(code_points, 16)
                if prop == 'SA':
                    if gen_category[cp] in ['Mn', 'Mc']:
                        prop = 'CM'
                    else:
                        prop = 'AL'
                interval = (cp, cp + 1, prop)
            if 'line' not in prop_ or 'SG' not in interval[2]: # Skip surrogates.
                intervals.append(interval)

    intervals = sorted(intervals)
    intervals_list = ''
    intervals_map = []
    num_intervals = 0
    for interval in intervals:
        if 128 < interval[1] - interval[0]:
            num_intervals += 1
            intervals_list += '    {}_interval{{{}, {}, {}::{}}},\n'.format(
                prop_, hex(interval[0]), hex(interval[1]), prop_enum, interval[2]
            )
        else:
            for i in range(interval[0], interval[1]):
                intervals_map.append((i, prop_names[interval[2]]))
    return (intervals_list, num_intervals, intervals_map)


def extract_bidi_bracket_properties(filename):
    retval = []
    bidi_brackets_lines = open(filename, 'r').readlines()
    for line in bidi_brackets_lines:
        line = line[:-1]
        if not line.startswith('#') and len(line) != 0:
            comment_start = line.find('#')
            comment = ''
            if comment_start != -1:
                comment = line[comment_start + 1:].strip()
                line = line[:comment_start]
            tokens = map(lambda x: x.strip(), line.split(';'))
            retval.append('{{0x{}, 0x{}, {}}},'.format(tokens[0], tokens[1], tokens[2] == 'o' and 'bidi_bracket_type::open' or 'bidi_bracket_type::close'))
    return retval

def extract_bidi_mirroring_properties(filename):
    values = []
    mapping = []
    bidi_mirroring_lines = open(filename, 'r').readlines()
    for line in bidi_mirroring_lines:
        line = line[:-1]
        if not line.startswith('#') and len(line) != 0:
            comment_start = line.find('#')
            comment = ''
            if comment_start != -1:
                comment = line[comment_start + 1:].strip()
                line = line[:comment_start]
            tokens = map(lambda x: x.strip(), line.split(';'))
            values.append('0x{},'.format(tokens[0]))
    for line in bidi_mirroring_lines:
        line = line[:-1]
        if not line.startswith('#') and len(line) != 0:
            comment_start = line.find('#')
            comment = ''
            if comment_start != -1:
                comment = line[comment_start + 1:].strip()
                line = line[:comment_start]
            tokens = map(lambda x: x.strip(), line.split(';'))
            mapping.append('{{0x{}, {}}},'.format(tokens[0], values.index('0x' + tokens[1] + ',')))
    return mapping, values


def uncompressed_prop_bytes(cp_prop_pairs):
    bytes_ = []
    for pair in cp_prop_pairs:
        lzw.add_cp(bytes_, pair[0])
        lzw.add_byte(bytes_, pair[1])
    return bytes_

def uncompressed_prop_lines(cp_prop_pairs):
    values_per_line = 18
    bytes_ = uncompressed_prop_bytes(cp_prop_pairs)
    return lzw.compressed_bytes_to_lines(bytes_, values_per_line)

def compressed_prop_lines(cp_prop_pairs):
    values_per_line = 12

    bytes_ = uncompressed_prop_bytes(cp_prop_pairs)
    compressed_bytes = lzw.compress(bytes_)

    #print 'rewrote {} * 64 = {} bits as {} * 8 = {} bits'.format(len(cp_prop_pairs), len(cp_prop_pairs)*64, len(bytes_), len(bytes_)*8)
    #print 'compressed to {} * 16 = {} bits'.format(len(compressed_bytes), len(compressed_bytes) * 16)

    return lzw.compressed_bytes_to_lines(compressed_bytes, values_per_line)

ext_pict_intervals = extract_extended_pictographic('emoji-data.txt')

grapheme_props = {
    'Other': 0,
    'CR': 1,
    'LF': 2,
    'Control': 3,
    'Extend': 4,
    'Regional_Indicator': 5,
    'Prepend': 6,
    'SpacingMark': 7,
    'L': 8,
    'V': 9,
    'T': 10,
    'LV': 11,
    'LVT': 12,
    'ExtPict': 13,
    'ZWJ': 14
}

(grapheme_break_intervals, num_grapheme_intervals, grapheme_break_intervals_map) = \
    extract_break_properties('GraphemeBreakProperty.txt', 'grapheme_prop',
                             grapheme_props, ext_pict_intervals)
bytes_, num_bytes = uncompressed_prop_lines(grapheme_break_intervals_map)
cpp_file = open('grapheme_break.cpp', 'w')
cpp_file.write(cpp_file_form.format('grapheme_prop', num_grapheme_intervals, grapheme_break_intervals, 'grapheme_break', bytes_, num_bytes, len(grapheme_break_intervals_map)))

word_props = {
    'Other': 0,
    'CR': 1,
    'LF': 2,
    'Newline': 3,
    'Katakana': 4,
    'ALetter': 5,
    'MidLetter': 6,
    'MidNum': 7,
    'MidNumLet': 8,
    'Numeric': 9,
    'ExtendNumLet': 10,
    'Regional_Indicator': 11,
    'Hebrew_Letter': 12,
    'Double_Quote': 13,
    'Single_Quote': 14,
    'ExtPict': 15,
    'WSegSpace': 16,
    'Format': 17,
    'Extend': 18,
    'ZWJ': 19
}

(word_break_intervals, num_word_intervals, word_break_intervals_map) = \
    extract_break_properties('WordBreakProperty.txt', 'word_prop',
                             word_props, ext_pict_intervals)
bytes_, num_bytes = uncompressed_prop_lines(word_break_intervals_map)
cpp_file = open('word_break.cpp', 'w')
cpp_file.write(cpp_file_form.format('word_prop', num_word_intervals, word_break_intervals, 'word_break', bytes_, num_bytes, len(word_break_intervals_map)))

sentence_props = {
    'Other': 0,
    'CR': 1,
    'LF': 2,
    'Sep': 3,
    'Sp': 4,
    'Lower': 5,
    'Upper': 6,
    'OLetter': 7,
    'Numeric': 8,
    'ATerm': 9,
    'STerm': 10,
    'Close': 11,
    'SContinue': 12,
    'Format': 13,
    'Extend': 14
}

(sentence_break_intervals, num_sentence_intervals, sentence_break_intervals_map) = \
    extract_break_properties('SentenceBreakProperty.txt', 'sentence_prop', sentence_props, [])
bytes_, num_bytes = uncompressed_prop_lines(sentence_break_intervals_map)
cpp_file = open('sentence_break.cpp', 'w')
cpp_file.write(cpp_file_form.format('sentence_prop', num_sentence_intervals, sentence_break_intervals, 'sentence_break', bytes_, num_bytes, len(sentence_break_intervals_map)))

line_props = {
    'AL': 0,
    'B2': 1,
    'BA': 2,
    'BB': 3,
    'BK': 4,
    'CB': 5,
    'CL': 6,
    'CP': 7,
    'CR': 8,
    'EX': 9,
    'GL': 10,
    'H2': 11,
    'H3': 12,
    'HL': 13,
    'HY': 14,
    'ID': 15,
    'IN': 16,
    'IS': 17,
    'JL': 18,
    'JT': 19,
    'JV': 20,
    'LF': 21,
    'NL': 22,
    'NS': 23,
    'NU': 24,
    'OP': 25,
    'PO': 26,
    'PR': 27,
    'QU': 28,
    'SP': 29,
    'SY': 30,
    'WJ': 31,
    'ZW': 32,
    'RI': 33,
    'EB': 34,
    'EM': 35,
    'CM': 36,
    'ZWJ': 37,
    'AI': 38,
    'XX': 39,
    'SA': 40,
    'CJ': 41
}

(line_break_intervals, num_line_intervals, line_break_intervals_map) = \
    extract_line_break_properties('LineBreak.txt', 'line_prop', line_props)
bytes_, num_bytes = uncompressed_prop_lines(line_break_intervals_map)
cpp_file = open('line_break.cpp', 'w')
cpp_file.write(cpp_file_form.format('line_prop', num_line_intervals, line_break_intervals, 'line_break', bytes_, num_bytes, len(line_break_intervals_map)))

bidi_props = {
    'L': 0,
    'R': 1,
    'EN': 2,
    'ES': 3,
    'ET': 4,
    'AN': 5,
    'CS': 6,
    'B': 7,
    'S': 8,
    'WS': 9,
    'ON': 10,
    'BN': 11,
    'NSM': 12,
    'AL': 13,
    'LRO': 14,
    'RLO': 15,
    'LRE': 16,
    'RLE': 17,
    'PDF': 18,
    'LRI': 19,
    'RLI': 20,
    'FSI': 21,
    'PDI': 22
}

(bidi_intervals, num_bidi_intervals, bidi_intervals_map) = \
    extract_break_properties('DerivedBidiClass.txt', 'bidi_prop', bidi_props, [])
bytes_, num_bytes = uncompressed_prop_lines(bidi_intervals_map)
cpp_file = open('bidi.cpp', 'w')
cpp_file.write(cpp_file_form.format('bidi_prop', num_bidi_intervals, bidi_intervals, 'bidirectional', bytes_, num_bytes, len(bidi_intervals_map)))

bidi_bracket_properties = extract_bidi_bracket_properties('BidiBrackets.txt')
bidi_bracket_properties_lines = '        ' + '\n        '.join(bidi_bracket_properties)
bidi_mirroring_mapping, bidi_mirroring_values = extract_bidi_mirroring_properties('BidiMirroring.txt')
bidi_mirroring_mapping_lines = '        ' + '\n        '.join(bidi_mirroring_mapping)
bidi_mirroring_values_lines = '        ' + '\n        '.join(bidi_mirroring_values)
hpp_file = open('bidirectional.hpp', 'w')
hpp_file.write(bidi_header_form.format(bidi_bracket_properties_lines, len(bidi_bracket_properties), bidi_mirroring_mapping_lines, len(bidi_mirroring_mapping), bidi_mirroring_values_lines))
