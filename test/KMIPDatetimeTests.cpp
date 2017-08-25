#include <string>
#include <iostream>
#include <gtest/gtest.h>

#include "KMIPDateTime.h"
#include "KMIPDefs.h"
#include "DateTime.h"
//#include "/usr/local/adios/include/adios.h"
#include <boost/date_time/special_defs.hpp>
using namespace boost::date_time;
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/local_time/local_date_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
using namespace boost::local_time;
#include <boost/date_time/local_time/local_time_io.hpp>

#include "strtk.hpp"
#include "datetime_utils.hpp"

TEST(KMIPDateTime, DateToString) {
    //adios_set_max_buffer_size(65);
    KMIPDateTime kdt(kmip::TagOriginalCreationDate);
    DateTime dt;
    EXPECT_TRUE(dt.fromString("%Y-%m-%dT%H:%M:%S%q", "2001-01-01T10:00:00+0700"));
    std::cerr << dt.toTime() << " " << dt.toString("%FT%T%z%Z") << std::endl;
    EXPECT_TRUE(dt.fromString("%Y-%m-%dT%H:%M:%S%Q", "2001-01-01T10:00:00-07:00"));
    std::cerr << dt.toTime() << " " << dt.toString("%FT%T%z%Z") << std::endl;
    dt = DateTime();
    std::cerr << dt.toString("%FT%T%z") << std::endl;
    std::cerr << dt.toString("%FT%T%z", true) << std::endl;

    std::string sTime = "2001-01-01 10:00:00 EST-5EDT,M4.1.0,M10.5.0";
    std::string sFormat = "%Y-%m-%d %H:%M:%S %ZP";
    local_time_input_facet *input_facet = new local_time_input_facet(sFormat);
    std::stringstream ss;
    ss.imbue(std::locale(ss.getloc(), input_facet));

    // This is our output date time.
    boost::local_time::local_date_time ldt(not_a_date_time);
    std::cerr << ldt.is_special() << ldt.is_not_a_date_time() << ldt << std::endl;


    // Read the timestamp into ldt.
    ss.str(sTime);
    ss >> ldt;
    std::cerr << ldt.is_special() << ldt.is_not_a_date_time() << ldt << std::endl;
    
    dt_utils::datetime udt;
    udt.clear();
    dt_utils::datetime_format19 fmt(udt);
    ASSERT_TRUE(strtk::string_to_type_converter("2001-01-01T10:00:00-07:00", fmt));
    std::cerr << udt.year << " " << udt.month << " " << udt.day << " " << udt.hour << ":" << udt.minute << ":" << udt.second << "." << udt.millisecond << " " << udt.tzd << std::endl;
    //udt.clear();
    //ASSERT_TRUE(strtk::string_to_type_converter("2001-01-01T10:00:00", fmt));
    //std::cerr << udt.year << " " << udt.month << " " << udt.day << " " << udt.hour << ":" << udt.minute << ":" << udt.second << "." << udt.millisecond << " " << udt.tzd << std::endl;
    EXPECT_TRUE(kdt.setValueFromXML("2001-01-01T10:00:00-07:00"));
    std::cerr << kdt.getXMLValue() << std::endl;
    EXPECT_TRUE(kdt.setValueFromXML("2001-01-01T10:00:00"));
    std::cerr << kdt.getXMLValue() << std::endl;
}
