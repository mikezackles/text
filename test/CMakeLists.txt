include_directories(${CMAKE_HOME_DIRECTORY})

include(CTest)

enable_testing()

add_custom_target(
    check
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_CURRENT_BINARY_DIR}/*.table
    COMMAND ${CMAKE_CTEST_COMMAND} -j4 -C ${CMAKE_CFG_INTDIR}
)

add_custom_target(
    bidi_tests
    COMMAND ${CMAKE_CTEST_COMMAND} -j4 -C ${CMAKE_CFG_INTDIR} -R bidi
)

set(LIMIT_TESTING_FOR_CI false CACHE BOOL "Timeouts kinda suck, so...")
set(LIMIT_TESTING_FOR_APPVEYOR false CACHE BOOL
    "Boost is installed, but linking to built Boost libs is problematic")

set(warnings_flag)
if (NOT MSVC)
    set(warnings_flag -Wall)
endif ()

if (LIMIT_TESTING_FOR_CI)
    if (MSVC)
        set(warnings_flag ${warnings_flag} /D LIMIT_TESTING_FOR_CI)
    else ()
        set(warnings_flag ${warnings_flag} -DLIMIT_TESTING_FOR_CI)
    endif ()
endif ()

set(coverage_gcda_files_0)
set(coverage_gcda_files_1)
set(coverage_gcda_files_2)
set(coverage_gcda_files_3)
set(coverage_gcda_files_4)
set(coverage_gcda_files_5)
set(coverage_gcda_files_6)

# This is used to generate some of the test files.  It is not a test.
add_executable(generate_tailoring_rule_tests generate_tailoring_rule_tests.cpp)
target_compile_options(generate_tailoring_rule_tests PRIVATE ${warnings_flag})
target_link_libraries(generate_tailoring_rule_tests text gtest gtest_main)
set_property(TARGET generate_tailoring_rule_tests PROPERTY CXX_STANDARD ${CXX_STD})
if (clang_on_linux)
    target_link_libraries(generate_tailoring_rule_tests c++)
endif ()

macro(add_test_executable name group)
    set(local_name ${name}_g${group})
    add_executable(${local_name} ${name}.cpp)
    target_compile_options(${local_name} PRIVATE ${warnings_flag})
    target_link_libraries(${local_name} text gtest gtest_main)
    if (ICU_FOUND AND NOT LIMIT_TESTING_FOR_CI)
        target_include_directories(${local_name} PRIVATE ${ICU_INCLUDE_DIR})
        target_link_libraries(
            ${local_name}
            ${ICU_LIBRARIES}
            ${ICU_IN_LIBRARY_RELEASE}
            ${ICU_DT_LIBRARY_RELEASE}
            ${ICU_UC_LIBRARY_RELEASE}
        )
    else ()
        target_compile_definitions(${local_name} PRIVATE -DNO_ICU)
    endif ()
    if (NOT MSVC AND NOT LIMIT_TESTING_FOR_CI) # Boost auto-linking handles this with MSVC.
        target_link_libraries(${local_name} boost_system boost_filesystem)
    endif ()
    if (MSVC)
        target_compile_options(${local_name} PRIVATE /source-charset:utf-8)
    endif ()
    set_property(TARGET ${local_name} PROPERTY CXX_STANDARD ${CXX_STD})
    add_test(${local_name} ${CMAKE_CURRENT_BINARY_DIR}/${local_name} --gtest_catch_exceptions=1)
    if (clang_on_linux)
        target_link_libraries(${local_name} c++)
    endif ()
    list(APPEND coverage_gcda_files_${group} ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${local_name}.dir/${local_name}.cpp.gcda)
    if (NOT "${ARGN}" STREQUAL "")
        foreach(arg ${ARGN})
            add_custom_command(
                TARGET ${local_name}
                POST_BUILD
                COMMAND
                    ${CMAKE_COMMAND} -E copy
                        ${CMAKE_CURRENT_SOURCE_DIR}/${arg}
                        ${CMAKE_CURRENT_BINARY_DIR}
            )
        endforeach()
    endif ()
endmacro()

add_test_executable(detail_utility 0)
add_test_executable(detail_iterator 0)
add_test_executable(utf8 0)
add_test_executable(utf16 0)
add_test_executable(transcode_algorithm 0)
add_test_executable(transcode_algorithm_no_simd 0)
add_test_executable(transcode_insert_iterator 0)
add_test_executable(transcode_view 0)
add_test_executable(grapheme_view 0)
add_test_executable(grapheme_iterator_api 0)
add_test_executable(string_view 0)
add_test_executable(string 0)
add_test_executable(string_builder 0)
add_test_executable(text_ 0)
add_test_executable(rope 0)
add_test_executable(detail_btree_util 0)
add_test_executable(detail_btree 0)
add_test_executable(detail_btree_2 0)
add_test_executable(detail_rope 0)
add_test_executable(detail_rope_btree 0)
add_test_executable(detail_rope_iterator 0)
add_test_executable(detail_vector_iterator 0)
add_test_executable(unencoded_rope_view 0)
add_test_executable(unencoded_rope 0)
add_test_executable(segmented_vector 0)
add_test_executable(common_op 0)
add_test_executable(trie_map_0 0)
add_test_executable(trie_map_1 0)
add_test_executable(detail_bidi 0)
add_test_executable(case_mapping 0)
add_test_executable(case_mapping_api 0)
add_test_executable(normalization_collation_api 0)

add_test_executable(break_api 0)
add_test_executable(text_algorithm 0)
add_test_executable(text_view_algorithm 0)
add_test_executable(rope_algorithm 0)
add_test_executable(rope_view_algorithm 0)
add_test_executable(string_algo 0)
add_test_executable(normalization_idempotence 0)
add_test_executable(relative_collation_test_non_ignorable_0 0)
add_test_executable(relative_collation_test_non_ignorable_1 0)
add_test_executable(relative_collation_test_non_ignorable_2 0)
add_test_executable(relative_collation_test_non_ignorable_3 0)
add_test_executable(relative_collation_test_non_ignorable_4 0)
add_test_executable(relative_collation_test_non_ignorable_5 0)
add_test_executable(relative_collation_test_non_ignorable_6 0)
add_test_executable(relative_collation_test_shifted_0 0)
add_test_executable(relative_collation_test_shifted_1 0)
add_test_executable(relative_collation_test_shifted_2 0)
add_test_executable(relative_collation_test_shifted_3 0)
add_test_executable(relative_collation_test_shifted_4 0)
add_test_executable(relative_collation_test_shifted_5 0)
add_test_executable(relative_collation_test_shifted_6 0)
add_test_executable(relative_collation_test_shifted_7 0)

add_test_executable(lexer 0)
add_test_executable(lexer_data 0)
add_test_executable(parser 0)
add_test_executable(parser_data 0)
add_test_executable(tailoring 0 riwords.txt)
add_test_executable(tailoring_reorderings 0)
add_test_executable(tailoring_suppressions 0)
add_test_executable(collation_search 0)

if (LIMIT_TESTING_FOR_CI)
    file(GLOB grapheme_break_tests grapheme_break_00.cpp)
    file(GLOB grapheme_iterator_tests grapheme_iterator_00.cpp)
    file(GLOB word_break_tests word_break_00.cpp)
    file(GLOB sentence_break_tests sentence_break_00.cpp)
    file(GLOB line_break_tests line_break_00.cpp)
    file(GLOB normalize_to_nfd_tests normalize_to_nfd_000.cpp)
    file(GLOB normalize_to_nfkd_tests normalize_to_nfkd_000.cpp)
    file(GLOB normalize_to_nfc_tests normalize_to_nfc_000.cpp)
    file(GLOB normalize_to_nfkc_tests normalize_to_nfkc_000.cpp)
    file(GLOB tailoring_rule_tests tailoring_rule_test_gu_standard_000.cpp)
    file(GLOB bidi_tests_a bidi_test_000.cpp)
    file(GLOB bidi_character_tests bidi_character_test_000.cpp)
else()
    file(GLOB grapheme_break_tests grapheme_break_??.cpp)
    file(GLOB grapheme_iterator_tests grapheme_iterator_??.cpp)
    file(GLOB word_break_tests word_break_??.cpp)
    file(GLOB sentence_break_tests sentence_break_??.cpp)
    file(GLOB line_break_tests line_break_??.cpp)
    file(GLOB bidi_tests_a bidi_test_[0-4]??.cpp)
    file(GLOB bidi_tests_b bidi_test_[5-9]??.cpp)
    file(GLOB bidi_character_tests bidi_character_test_???.cpp)
    file(GLOB normalize_to_nfd_tests normalize_to_nfd_???.cpp)
    file(GLOB normalize_to_nfkd_tests normalize_to_nfkd_???.cpp)
    file(GLOB normalize_to_nfc_tests normalize_to_nfc_???.cpp)
    file(GLOB normalize_to_nfkc_tests normalize_to_nfkc_???.cpp)
    file(GLOB tailoring_rule_tests tailoring_rule_test_*.cpp)
endif()

set(globbed_tests
    ${grapheme_break_tests}
    ${grapheme_iterator_tests}
    ${word_break_tests}
    ${sentence_break_tests}
    ${line_break_tests}
)

foreach(test ${globbed_tests})
    get_filename_component(test_name ${test} NAME_WE)
    add_test_executable(${test_name} 1)
endforeach()

foreach(test ${bidi_tests_a})
    get_filename_component(test_name ${test} NAME_WE)
    add_test_executable(${test_name} 2)
endforeach()

foreach(test ${bidi_tests_b})
    get_filename_component(test_name ${test} NAME_WE)
    add_test_executable(${test_name} 3)
endforeach()

foreach(test ${bidi_character_tests})
    get_filename_component(test_name ${test} NAME_WE)
    add_test_executable(${test_name} 4)
endforeach()

set(globbed_tests
    ${normalize_to_nfd_tests}
    ${normalize_to_nfkd_tests}
    ${normalize_to_nfc_tests}
    ${normalize_to_nfkc_tests}
)

foreach(test ${globbed_tests})
    get_filename_component(test_name ${test} NAME_WE)
    add_test_executable(${test_name} 5)
endforeach()

foreach(test ${tailoring_rule_tests})
    get_filename_component(test_name ${test} NAME_WE)
    add_test_executable(${test_name} 6)
endforeach()

set(all_coverage_gcda_files
    ${coverage_gcda_files_0}
    ${coverage_gcda_files_1}
    ${coverage_gcda_files_2}
    ${coverage_gcda_files_3}
    ${coverage_gcda_files_4}
    ${coverage_gcda_files_5}
    ${coverage_gcda_files_6}
)

if (BUILD_COVERAGE AND UNIX)
    if (APPLE)
        add_custom_target(
            coverage
            rm -rf lcov-all.info lcov.info output ${all_coverage_gcda_files}
            COMMAND
                ${CMAKE_CTEST_COMMAND} -VV -C ${CMAKE_CFG_INTDIR}
            COMMAND
                cd ${CMAKE_BINARY_DIR}
            COMMAND
                llvm-cov gcov -f -b ${call_overage_gcda_files}
            COMMAND
                lcov --directory . --base-directory . --gcov-tool ${CMAKE_SOURCE_DIR}/llvm-gcov.sh --capture -o lcov-all.info
            COMMAND
                lcov -e lcov-all.info ${CMAKE_SOURCE_DIR}/include/boost/text/* ${CMAKE_SOURCE_DIR}/include/boost/text/detail/* -o lcov.info
            COMMAND
                genhtml lcov.info -o output
        )
    else ()
        add_custom_target(
            coverage
            rm -rf lcov-all.info lcov.info output ${all_coverage_gcda_files}
            COMMAND
                echo "Group 0 ..."
            COMMAND
                ${CMAKE_CTEST_COMMAND} -j4 -VV -C ${CMAKE_CFG_INTDIR} -R _g0
            COMMAND
                echo "Group 1 ..."
            COMMAND
                ${CMAKE_CTEST_COMMAND} -j4 -VV -C ${CMAKE_CFG_INTDIR} -R _g1
            COMMAND
                echo "Group 2 ..."
            COMMAND
                ${CMAKE_CTEST_COMMAND} -j4 -VV -C ${CMAKE_CFG_INTDIR} -R _g2
            COMMAND
                echo "Group 3 ..."
            COMMAND
                ${CMAKE_CTEST_COMMAND} -j4 -VV -C ${CMAKE_CFG_INTDIR} -R _g3
            COMMAND
                echo "Group 4 ..."
            COMMAND
                ${CMAKE_CTEST_COMMAND} -j4 -VV -C ${CMAKE_CFG_INTDIR} -R _g4
            COMMAND
                echo "Group 5 ..."
            COMMAND
                ${CMAKE_CTEST_COMMAND} -j4 -VV -C ${CMAKE_CFG_INTDIR} -R _g5
            COMMAND
                echo "Group 6 ..."
            COMMAND
                ${CMAKE_CTEST_COMMAND} -j4 -VV -C ${CMAKE_CFG_INTDIR} -R _g6
            COMMAND
                cd ${CMAKE_BINARY_DIR}
            COMMAND
                echo "gcov Group 0 ..."
            COMMAND
                gcov -f -b ${coverage_gcda_files_0}
            COMMAND
                echo "gcov Group 1 ..."
            COMMAND
                gcov -f -b ${coverage_gcda_files_1}
            COMMAND
                echo "gcov Group 2 ..."
            COMMAND
                gcov -f -b ${coverage_gcda_files_2}
            COMMAND
                echo "gcov Group 3 ..."
            COMMAND
                gcov -f -b ${coverage_gcda_files_3}
            COMMAND
                echo "gcov Group 4 ..."
            COMMAND
                gcov -f -b ${coverage_gcda_files_4}
            COMMAND
                echo "gcov Group 5 ..."
            COMMAND
                gcov -f -b ${coverage_gcda_files_5}
            COMMAND
                echo "gcov Group 6 ..."
            COMMAND
                gcov -f -b ${coverage_gcda_files_6}
            COMMAND
                echo "lcov 0 ..."
            COMMAND
                lcov --directory . --base-directory . --capture -o lcov-all.info
            COMMAND
                echo "lcov 1 ..."
            COMMAND
                lcov -e lcov-all.info ${CMAKE_SOURCE_DIR}/include/boost/text/* ${CMAKE_SOURCE_DIR}/include/boost/text/detail/* -o lcov.info
            COMMAND
                echo "genhtml ..."
            COMMAND
                genhtml lcov.info -o output
        )
    endif ()
endif ()

set(compile_sources
    compile_tests_main.cpp
    compile_include_string_view_1.cpp
    compile_include_string_view_2.cpp
    compile_include_string_view_3.cpp
    compile_include_string_1.cpp
    compile_include_string_2.cpp
    compile_include_string_3.cpp
    compile_include_unencoded_rope_view_1.cpp
    compile_include_unencoded_rope_view_2.cpp
    compile_include_unencoded_rope_view_3.cpp
    compile_include_unencoded_rope_1.cpp
    compile_include_unencoded_rope_2.cpp
    compile_include_unencoded_rope_3.cpp
    compile_include_text_view_1.cpp
    compile_include_text_view_2.cpp
    compile_include_text_view_3.cpp
    compile_include_text_1.cpp
    compile_include_text_2.cpp
    compile_include_text_3.cpp
    compile_include_rope_view_1.cpp
    compile_include_rope_view_2.cpp
    compile_include_rope_view_3.cpp
    compile_include_rope_1.cpp
    compile_include_rope_2.cpp
    compile_include_rope_3.cpp
    compile_include_trie_1.cpp
    compile_include_trie_2.cpp
    compile_include_trie_map_1.cpp
    compile_include_trie_map_2.cpp
    compile_include_trie_set_1.cpp
    compile_include_trie_set_2.cpp
    compile_include_vector_1.cpp
    compile_include_vector_2.cpp
    compile_include_algorithm_1.cpp
    compile_include_algorithm_2.cpp
    compile_detail_is_char_iter.cpp
    compile_detail_is_char_range.cpp
    compile_detail_is_cp_iter.cpp
    compile_trie_conversions.cpp
)

# Set to true to compile the headers with BOOST_TEXT_DOXYGEN defined
if (false)
    set(compile_sources
      ${compile_sources}
      compile_include_string_view_doxygen.cpp
      compile_include_string_doxygen.cpp
      compile_include_unencoded_rope_view_doxygen.cpp
      compile_include_unencoded_rope_doxygen.cpp
      compile_include_algorithm_doxygen.cpp
      compile_include_utf8_doxygen.cpp
    )
endif ()

add_executable(compile_tests ${compile_sources})
target_compile_options(compile_tests PRIVATE ${warnings_flag})
target_link_libraries(compile_tests text)
set_property(TARGET compile_tests PROPERTY CXX_STANDARD ${CXX_STD})
if (clang_on_linux)
    target_link_libraries(compile_tests c++)
endif ()

if (BUILD_ROPE_THREADSAFETY_TEST)
    if (USE_ASAN OR USE_UBSAN)
        message(FATAL_ERROR "BUILD_ROPE_THREADSAFETY_TEST must not be enabled at the same time as USE_ASAN or USE_UBSAN")
    endif ()
    add_executable(rope_threadsafety rope_threadsafety.cpp)
    target_compile_options(rope_threadsafety PRIVATE ${warnings_flag} -fsanitize=thread)
    target_link_libraries(rope_threadsafety text -fsanitize=thread)
    if (UNIX AND NOT APPLE) # Linux
        target_compile_options(rope_threadsafety PRIVATE -pthread)
        target_link_libraries(rope_threadsafety -pthread)
    endif ()
    set_property(TARGET rope_threadsafety PROPERTY CXX_STANDARD ${CXX_STD})
    add_test(rope_threadsafety ${CMAKE_CURRENT_BINARY_DIR}/rope_threadsafety)
    if (clang_on_linux)
        target_link_libraries(rope_threadsafety c++)
    endif ()
endif ()

if (BUILD_FUZZ_TESTS)
    if (NOT USE_ASAN AND NOT USE_UBSAN)
        message("BUILD_FUZZ_TEST would greatly benefit from also turning on USE_ASAN or USE_UBSAN")
    endif ()

    file(GLOB fuzzer_sources ${CMAKE_CURRENT_SOURCE_DIR}/Fuzzer/*.cpp)
    add_library(Fuzzer STATIC ${fuzzer_sources})
    target_compile_options(Fuzzer PRIVATE -g -O2 -fno-omit-frame-pointer -std=c++11)

    add_executable(fuzz_rope fuzz_rope.cpp)
    target_compile_options(fuzz_rope PRIVATE ${warnings_flag} -fsanitize-coverage=trace-pc -fsanitize=address)
    target_link_libraries(fuzz_rope text Fuzzer -fsanitize-coverage=trace-pc -fsanitize=address)
    set_property(TARGET fuzz_rope PROPERTY CXX_STANDARD ${CXX_STD})
    add_test(fuzz_rope
             ${CMAKE_CURRENT_BINARY_DIR}/fuzz_rope
             -max_total_time=30)
    if (clang_on_linux)
        target_link_libraries(fuzz_rope c++)
    endif ()

    add_executable(fuzz_segmented_vector fuzz_segmented_vector.cpp)
    target_compile_options(fuzz_segmented_vector PRIVATE ${warnings_flag} -fsanitize-coverage=trace-pc -fsanitize=address)
    target_link_libraries(fuzz_segmented_vector text Fuzzer -fsanitize-coverage=trace-pc -fsanitize=address)
    set_property(TARGET fuzz_segmented_vector PROPERTY CXX_STANDARD ${CXX_STD})
    add_test(fuzz_segmented_vector
             ${CMAKE_CURRENT_BINARY_DIR}/fuzz_segmented_vector
             -max_total_time=30)
    if (clang_on_linux)
        target_link_libraries(fuzz_segmented_vector c++)
    endif ()

    add_executable(fuzz_trie fuzz_trie.cpp)
    target_compile_options(fuzz_trie PRIVATE ${warnings_flag} -fsanitize-coverage=trace-pc -fsanitize=address)
    target_link_libraries(fuzz_trie text Fuzzer -fsanitize-coverage=trace-pc -fsanitize=address)
    set_property(TARGET fuzz_trie PROPERTY CXX_STANDARD ${CXX_STD})
    add_test(fuzz_trie
             ${CMAKE_CURRENT_BINARY_DIR}/fuzz_trie
             -max_len=16 -only_ascii=1 -max_total_time=30)
    if (clang_on_linux)
        target_link_libraries(fuzz_trie c++)
    endif ()
endif ()
