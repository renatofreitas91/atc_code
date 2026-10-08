cmake_minimum_required(VERSION 3.20)

project(AdvancedTrigonometryCalculator VERSION 2.1.9 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

set(ATC_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Advanced Trigonometry Calculator")

set(ATC_COMMON_SOURCES
    "${ATC_SOURCE_DIR}/arithmetic.cpp"
    "${ATC_SOURCE_DIR}/arithmetic_matrix_solver.cpp"
    "${ATC_SOURCE_DIR}/atc_core.cpp"
    "${ATC_SOURCE_DIR}/auto_complete.cpp"
    "${ATC_SOURCE_DIR}/boolean_evaluator.cpp"
    "${ATC_SOURCE_DIR}/commands.cpp"
    "${ATC_SOURCE_DIR}/conversions.cpp"
    "${ATC_SOURCE_DIR}/data_processing_core.cpp"
    "${ATC_SOURCE_DIR}/derivatives.cpp"
    "${ATC_SOURCE_DIR}/digital_signal_processing.cpp"
    "${ATC_SOURCE_DIR}/dynamic_allocations.cpp"
    "${ATC_SOURCE_DIR}/equation_solver.cpp"
    "${ATC_SOURCE_DIR}/equations_system_solver.cpp"
    "${ATC_SOURCE_DIR}/financial_calculations.cpp"
    "${ATC_SOURCE_DIR}/function_study.cpp"
    "${ATC_SOURCE_DIR}/geometry_calculations.cpp"
    "${ATC_SOURCE_DIR}/graph.cpp"
    "${ATC_SOURCE_DIR}/hyperbolic.cpp"
    "${ATC_SOURCE_DIR}/integral_solver.cpp"
    "${ATC_SOURCE_DIR}/logarithmic.cpp"
    "${ATC_SOURCE_DIR}/main.cpp"
    "${ATC_SOURCE_DIR}/main_aux_processor.cpp"
    "${ATC_SOURCE_DIR}/main_processor.cpp"
    "${ATC_SOURCE_DIR}/microeconomics_calculations.cpp"
    "${ATC_SOURCE_DIR}/numerical_systems.cpp"
    "${ATC_SOURCE_DIR}/physics_calculations.cpp"
    "${ATC_SOURCE_DIR}/polynomial_arithmetic.cpp"
    "${ATC_SOURCE_DIR}/processing_core.cpp"
    "${ATC_SOURCE_DIR}/safe_chararray.cpp"
    "${ATC_SOURCE_DIR}/scripting.cpp"
    "${ATC_SOURCE_DIR}/settings.cpp"
    "${ATC_SOURCE_DIR}/solver.cpp"
    "${ATC_SOURCE_DIR}/sorting.cpp"
    "${ATC_SOURCE_DIR}/statistics.cpp"
    "${ATC_SOURCE_DIR}/statistics_calculations.cpp"
    "${ATC_SOURCE_DIR}/time.cpp"
    "${ATC_SOURCE_DIR}/triangles_rectangles_solver.cpp"
    "${ATC_SOURCE_DIR}/trigonometry.cpp"
)

add_executable(atc ${ATC_COMMON_SOURCES})
target_link_libraries(atc PRIVATE Boost::headers Threads::Threads)

if(WIN32)
    target_sources(atc PRIVATE
        "${ATC_SOURCE_DIR}/check_for_updates.cpp"
        "${ATC_SOURCE_DIR}/crash_handler.cpp"
        "${ATC_SOURCE_DIR}/xp_compat.cpp"
    )
    target_compile_definitions(atc PRIVATE
        _CRT_SECURE_NO_WARNINGS
        BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
    )
    target_link_libraries(atc PRIVATE winhttp wininet shell32 dbghelp)
else()
    message(STATUS
        "ATC 2.1.9 Linux portability bootstrap: Windows-only update, crash, "
        "and XP compatibility units are excluded. Remaining Win32 coupling "
        "is intentionally left visible for the first compiler-driven audit."
    )
endif()

if(MSVC)
    target_compile_options(atc PRIVATE /W4)
else()
    target_compile_options(atc PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Ubuntu 22.04 ships Boost 1.74, whose signed/unsigned type traits use
    # static members of an internal unnamed enum. GCC diagnoses their ODR use
    # while generating commands.cpp in C++17 Release mode. Keep the
    # compatibility exception isolated to that translation unit.
    set_source_files_properties(
        "${ATC_SOURCE_DIR}/commands.cpp"
        PROPERTIES COMPILE_OPTIONS "-fpermissive"
    )
endif()
