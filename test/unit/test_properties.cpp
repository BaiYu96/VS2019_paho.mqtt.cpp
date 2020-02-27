// test_properties.cpp
//
// Catch2 unit tests for the 'property' and 'properties' classes in the
// Eclipse Paho MQTT C++ library.
//

#include <iostream>
#include <cstring>
#include "catch2/catch.hpp"
#include "mqtt/properties.h"

using namespace mqtt;

inline bool stringcmp(char* cstr, const string& s) {
	return std::memcmp(cstr, s.data(), s.length()) == 0;
}

/////////////////////////////////////////////////////////////////////////////
// property

TEST_CASE("int property constructor", "[property]") {
    // This is a known byte property
    SECTION("creating a byte property") {
		property::code typ = property::PAYLOAD_FORMAT_INDICATOR;

		property prop { typ, 42 };

		REQUIRE(prop.c_struct().identifier == MQTTPROPERTY_CODE_PAYLOAD_FORMAT_INDICATOR);
		REQUIRE(prop.c_struct().value.byte == 42);

		REQUIRE(prop.type() == typ);
		REQUIRE(get<uint8_t>(prop) == uint8_t(42));
    }

	SECTION("creating a bad byte property") {
		// TODO: Test constructor for out of range input
	}

    // This is a known 2-byte integer property
    SECTION("creating an int2 property") {
		property::code typ = property::TOPIC_ALIAS;

		property prop { typ, 512 };

		REQUIRE(prop.c_struct().identifier == MQTTPROPERTY_CODE_TOPIC_ALIAS);
		REQUIRE(prop.c_struct().value.integer2 == 512);

		REQUIRE(prop.type() == typ);
		REQUIRE(get<int16_t>(prop) == int16_t(512));
    }

	SECTION("creating a bad int2 property") {
		// TODO: Test constructor for out of range input
	}

    // This is a known 4-byte integer property
    SECTION("creating an int4 property") {
		property::code typ = property::MESSAGE_EXPIRY_INTERVAL;

		property prop { typ, 70000 };

		REQUIRE(prop.c_struct().identifier == MQTTPROPERTY_CODE_MESSAGE_EXPIRY_INTERVAL);
		REQUIRE(prop.c_struct().value.integer4 == 70000);

		REQUIRE(prop.type() == typ);
		REQUIRE(get<int32_t>(prop) == int32_t(70000));
    }

	SECTION("creating a bad int2 property") {
		// TODO: Test constructor for out of range input
	}
}

TEST_CASE("string property constructor", "[property]") {
	property::code typ = property::RESPONSE_TOPIC;

	SECTION("property from string") {
		string topic { "replies/bubba" };

		property prop { typ, topic };

		REQUIRE(prop.c_struct().identifier == MQTTPROPERTY_CODE_RESPONSE_TOPIC);
		REQUIRE(prop.c_struct().value.data.len == int(topic.length()));
		REQUIRE(stringcmp(prop.c_struct().value.data.data, topic));

		REQUIRE(prop.type() == typ);
		REQUIRE(get<string>(prop) == topic);
	}

	SECTION("property from c-string") {
		const char* topic = "replies/bubba";
		size_t n = std::strlen(topic);

		property prop { typ, topic };

		REQUIRE(prop.c_struct().identifier == MQTTPROPERTY_CODE_RESPONSE_TOPIC);
		REQUIRE(prop.c_struct().value.data.len == int(n));
		REQUIRE(std::memcmp(prop.c_struct().value.data.data, topic, n) == 0);

		REQUIRE(prop.type() == typ);
		REQUIRE(get<string>(prop) == string(topic, n));
	}
}


TEST_CASE("binary property constructor", "[property]") {
	SECTION("property from binary") {
		property::code typ = property::CORRELATION_DATA;
		const size_t LEN = 5;
		binary corr_id { "\x00\x01\x02\x03\x04", LEN };

		property prop { property::CORRELATION_DATA, corr_id };

		REQUIRE(prop.c_struct().identifier == MQTTPROPERTY_CODE_CORRELATION_DATA);
		REQUIRE(prop.c_struct().value.data.len == int(corr_id.length()));
		REQUIRE(std::memcmp(prop.c_struct().value.data.data, corr_id.data(), LEN) == 0);

		REQUIRE(prop.type() == typ);
		REQUIRE(get<binary>(prop) == corr_id);
	}
}


TEST_CASE("string pair property constructor", "[property]") {
	property::code typ = property::USER_PROPERTY;

	SECTION("property from strings") {
		string	name { "bubba" },
				value { "some val" };

		property prop { typ, name, value };

		REQUIRE(prop.c_struct().identifier == MQTTPROPERTY_CODE_USER_PROPERTY);

		REQUIRE(prop.c_struct().value.data.len == int(name.length()));
		REQUIRE(stringcmp(prop.c_struct().value.data.data, name));

		REQUIRE(prop.c_struct().value.value.len == int(value.length()));
		REQUIRE(stringcmp(prop.c_struct().value.value.data, value));

		REQUIRE(prop.type() == typ);

		auto usr = get<string_pair>(prop);
		REQUIRE(std::get<0>(usr) == name);
		REQUIRE(std::get<1>(usr) == value);
	}

	SECTION("property from c-strings") {
		const char* name = "bubba";
		size_t name_len = strlen(name);

		const char* value = "some val";
		size_t value_len = strlen(value);

		property prop { typ, name, value };

		REQUIRE(prop.c_struct().identifier == MQTTPROPERTY_CODE_USER_PROPERTY);

		REQUIRE(prop.c_struct().value.data.len == name_len);
		REQUIRE(std::memcmp(prop.c_struct().value.data.data, name, name_len) == 0);

		REQUIRE(prop.c_struct().value.value.len == value_len);
		REQUIRE(std::memcmp(prop.c_struct().value.value.data, value, value_len) == 0);

		REQUIRE(prop.type() == typ);

		auto usr = get<string_pair>(prop);
		REQUIRE(std::get<0>(usr) == string(name, name_len));
		REQUIRE(std::get<1>(usr) == string(value, value_len));
	}
}

TEST_CASE("int property copy constructor", "[property]") {
    SECTION("copy an int4 property") {
		property::code typ = property::MESSAGE_EXPIRY_INTERVAL;

		property org_prop { typ, 70000 };
		property prop { org_prop };

		REQUIRE(prop.c_struct().identifier == MQTTPROPERTY_CODE_MESSAGE_EXPIRY_INTERVAL);
		REQUIRE(prop.c_struct().value.integer4 == 70000);

		REQUIRE(prop.type() == typ);
		REQUIRE(get<int32_t>(prop) == int32_t(70000));
    }
}

TEST_CASE("int property move constructor", "[property]") {
    SECTION("move an int4 property") {
		property::code typ = property::MESSAGE_EXPIRY_INTERVAL;

		property org_prop { typ, 70000 };
		property prop { std::move(org_prop) };

		REQUIRE(prop.c_struct().identifier == MQTTPROPERTY_CODE_MESSAGE_EXPIRY_INTERVAL);
		REQUIRE(prop.c_struct().value.integer4 == 70000);

		REQUIRE(prop.type() == typ);
		REQUIRE(get<int32_t>(prop) == int32_t(70000));

		// Make sure the old value was moved
		REQUIRE(org_prop.c_struct().identifier == 0);
		REQUIRE(org_prop.c_struct().value.integer4 == 0);
    }
}

TEST_CASE("string property copy constructor", "[property]") {
	SECTION("copy a string property") {
		property::code typ = property::RESPONSE_TOPIC;
		string topic { "replies/bubba" };

		property org_prop { typ, topic };
		property prop { org_prop };

		REQUIRE(prop.c_struct().identifier == MQTTPROPERTY_CODE_RESPONSE_TOPIC);

		REQUIRE(prop.c_struct().value.data.len == int(topic.length()));
		REQUIRE(std::memcmp(prop.c_struct().value.data.data, topic.data(), topic.length()) == 0);

		REQUIRE(prop.type() == typ);
		REQUIRE(get<string>(prop) == topic);
	}

	// Make sure the copy is still valid after the original disappears
	SECTION("copy a temp string property") {
		property::code typ = property::RESPONSE_TOPIC;
		string topic { "replies/bubba" };

		std::unique_ptr<property> org_prop{ new property { typ, topic } };
		property prop { *org_prop };
		org_prop.reset(nullptr);

		REQUIRE(prop.c_struct().identifier == MQTTPROPERTY_CODE_RESPONSE_TOPIC);

		REQUIRE(prop.c_struct().value.data.len == int(topic.length()));
		REQUIRE(std::memcmp(prop.c_struct().value.data.data, topic.data(), topic.length()) == 0);

		REQUIRE(prop.type() == typ);
		REQUIRE(get<string>(prop) == topic);
	}

}

TEST_CASE("string property move constructor", "[property]") {
	SECTION("move a string property") {
		property::code typ = property::RESPONSE_TOPIC;
		string topic { "replies/bubba" };

		property org_prop { typ, topic };
		property prop { std::move(org_prop) };

		REQUIRE(prop.c_struct().identifier == MQTTPROPERTY_CODE_RESPONSE_TOPIC);

		REQUIRE(prop.c_struct().value.data.len == int(topic.length()));
		REQUIRE(stringcmp(prop.c_struct().value.data.data, topic));

		REQUIRE(prop.type() == typ);
		REQUIRE(get<string>(prop) == topic);

		// Make sure the old value was moved
		REQUIRE(org_prop.c_struct().identifier == 0);
		REQUIRE(org_prop.c_struct().value.data.len == 0);
		REQUIRE(org_prop.c_struct().value.data.data == nullptr);
	}
}

TEST_CASE("string pair property copy constructor", "[property]") {
	property::code typ = property::USER_PROPERTY;

	SECTION("property from strings") {
		string	name { "bubba" },
				value { "some val" };

		property org_prop { typ, name, value };
		property prop { org_prop };

		REQUIRE(prop.c_struct().identifier == MQTTPROPERTY_CODE_USER_PROPERTY);

		REQUIRE(prop.c_struct().value.data.len == int(name.length()));
		REQUIRE(stringcmp(prop.c_struct().value.data.data, name));

		REQUIRE(prop.c_struct().value.value.len == int(value.length()));
		REQUIRE(stringcmp(prop.c_struct().value.value.data, value));

		REQUIRE(prop.type() == typ);

		auto usr = get<string_pair>(prop);
		REQUIRE(std::get<0>(usr) == name);
		REQUIRE(std::get<1>(usr) == value);
	}

	// Make sure the property is still valid after the original disappears
	SECTION("property from temp strings property") {
		string	name { "bubba" },
				value { "some val" };

		std::unique_ptr<property> org_prop{ new property { typ, name, value } };
		property prop { *org_prop };
		org_prop.reset(nullptr);

		REQUIRE(prop.c_struct().identifier == MQTTPROPERTY_CODE_USER_PROPERTY);

		REQUIRE(prop.c_struct().value.data.len == int(name.length()));
		REQUIRE(stringcmp(prop.c_struct().value.data.data, name));

		REQUIRE(prop.c_struct().value.value.len == int(value.length()));
		REQUIRE(stringcmp(prop.c_struct().value.value.data, value));

		REQUIRE(prop.type() == typ);

		auto usr = get<string_pair>(prop);
		REQUIRE(std::get<0>(usr) == name);
		REQUIRE(std::get<1>(usr) == value);
	}
}


TEST_CASE("string pair property move constructor", "[property]") {
	property::code typ = property::USER_PROPERTY;

	SECTION("property from strings") {
		string	name { "bubba" },
				value { "some val" };

		property org_prop { typ, name, value };
		property prop { std::move(org_prop) };

		REQUIRE(prop.c_struct().identifier == MQTTPROPERTY_CODE_USER_PROPERTY);

		REQUIRE(prop.c_struct().value.data.len == int(name.length()));
		REQUIRE(stringcmp(prop.c_struct().value.data.data, name));

		REQUIRE(prop.c_struct().value.value.len == int(value.length()));
		REQUIRE(stringcmp(prop.c_struct().value.value.data, value));

		REQUIRE(prop.type() == typ);

		auto usr = get<string_pair>(prop);
		REQUIRE(std::get<0>(usr) == name);
		REQUIRE(std::get<1>(usr) == value);

		// Make sure the old value was moved
		REQUIRE(org_prop.c_struct().identifier == 0);
		REQUIRE(org_prop.c_struct().value.data.len == 0);
		REQUIRE(org_prop.c_struct().value.data.data == nullptr);
		REQUIRE(org_prop.c_struct().value.value.len == 0);
		REQUIRE(org_prop.c_struct().value.value.data == nullptr);
	}
}

/////////////////////////////////////////////////////////////////////////////
// properties

TEST_CASE("properties constructor", "[properties]") {
    SECTION("properties default constructor") {
		properties props;

		REQUIRE(props.size() == 0);
		REQUIRE(props.byte_length() == 1);
	}
}

TEST_CASE("properties add", "[properties]") {
    SECTION("properties adding items") {
		properties props;
		REQUIRE(props.size() == 0);

		props.add({property::PAYLOAD_FORMAT_INDICATOR, 42});
		REQUIRE(props.size() == 1);

		props.add({property::MESSAGE_EXPIRY_INTERVAL, 70000});
		REQUIRE(props.size() == 2);
	}
}

TEST_CASE("properties clear", "[properties]") {
    SECTION("properties clear") {
		properties props;
		props.add({property::PAYLOAD_FORMAT_INDICATOR, 42});
		props.add({property::MESSAGE_EXPIRY_INTERVAL, 70000});
		REQUIRE(props.size() == 2);

		props.clear();
		REQUIRE(props.size() == 0);
		REQUIRE(props.byte_length() == 1);
	}
}

TEST_CASE("properties count and contains", "[properties]") {
    SECTION("single count properties") {
		properties props;

		REQUIRE(props.count(property::PAYLOAD_FORMAT_INDICATOR) == 0);
		REQUIRE(!props.contains(property::PAYLOAD_FORMAT_INDICATOR));

		props.add({property::PAYLOAD_FORMAT_INDICATOR, 42});
		REQUIRE(props.count(property::PAYLOAD_FORMAT_INDICATOR) == 1);
		REQUIRE(props.contains(property::PAYLOAD_FORMAT_INDICATOR));

		props.add({property::MESSAGE_EXPIRY_INTERVAL, 70000});
		REQUIRE(props.count(property::MESSAGE_EXPIRY_INTERVAL) == 1);

		// Make sure adding expirary didn't affect format ind
		REQUIRE(props.count(property::PAYLOAD_FORMAT_INDICATOR) == 1);
		REQUIRE(props.contains(property::PAYLOAD_FORMAT_INDICATOR));
	}

	/*
    SECTION("single count properties with multi add") {
		properties props;

		props.add({property::PAYLOAD_FORMAT_INDICATOR, 42});
		REQUIRE(props.count(property::PAYLOAD_FORMAT_INDICATOR) == 1);

		// Can't add again
		props.add({property::PAYLOAD_FORMAT_INDICATOR, 16});
		REQUIRE(props.count(property::PAYLOAD_FORMAT_INDICATOR) == 1);
	}
	*/

    SECTION("multi count properties") {
		properties props;

		REQUIRE(props.count(property::USER_PROPERTY) == 0);

		props.add({property::USER_PROPERTY, "usr1", "bubba"});
		REQUIRE(props.count(property::USER_PROPERTY) == 1);

		props.add({property::USER_PROPERTY, "usr2", "wally"});
		REQUIRE(props.count(property::USER_PROPERTY) == 2);

		props.add({property::USER_PROPERTY, "usr3", "some longer property value"});
		REQUIRE(props.count(property::USER_PROPERTY) == 3);
	}
}

TEST_CASE("getting properties", "[properties]") {
    SECTION("integer properties") {
		const uint8_t FMT_IND = 42;
		const uint16_t TOP_ALIAS = 511;
		const uint32_t MAX_PKT_SZ = 32*1024;

		properties props;
		props.add({property::PAYLOAD_FORMAT_INDICATOR, FMT_IND});
		props.add({property::MAXIMUM_PACKET_SIZE, MAX_PKT_SZ});
		props.add({property::TOPIC_ALIAS, TOP_ALIAS});

		auto fmtInd = props.get(property::PAYLOAD_FORMAT_INDICATOR);
		REQUIRE(get<uint8_t>(fmtInd) == FMT_IND);

		auto topAlias = props.get(property::TOPIC_ALIAS);
		REQUIRE(get<uint16_t>(topAlias) == TOP_ALIAS);

		auto maxPktSz = props.get(property::MAXIMUM_PACKET_SIZE);
		REQUIRE(get<uint32_t>(maxPktSz) == MAX_PKT_SZ);
	}

    SECTION("integer properties with typed get") {
		const uint8_t FMT_IND = 42;
		const uint16_t TOP_ALIAS = 511;
		const uint32_t MAX_PKT_SZ = 32*1024;

		properties props;
		props.add({property::PAYLOAD_FORMAT_INDICATOR, FMT_IND});
		props.add({property::MAXIMUM_PACKET_SIZE, MAX_PKT_SZ});
		props.add({property::TOPIC_ALIAS, TOP_ALIAS});

		REQUIRE(get<uint8_t>(props, property::PAYLOAD_FORMAT_INDICATOR) == FMT_IND);
		REQUIRE(get<uint16_t>(props, property::TOPIC_ALIAS) == TOP_ALIAS);
		REQUIRE(get<uint32_t>(props, property::MAXIMUM_PACKET_SIZE) == MAX_PKT_SZ);
	}

    SECTION("string properties") {
		string topic { "replies/bubba" };
		binary corr_id { "\x00\x01\x02\x03\x04", 5 };

		properties props;
		props.add({property::RESPONSE_TOPIC, topic});
		props.add({property::CORRELATION_DATA, corr_id});

		REQUIRE(get<string>(props, property::RESPONSE_TOPIC) == topic);
		REQUIRE(get<binary>(props, property::CORRELATION_DATA) == corr_id);
	}

    SECTION("string pair properties") {
		const string	NAME1  { "usr1" },
						NAME2  { "usr2" },
						VALUE1 { "this is value one" },
						VALUE2 { "this is value two" };

		properties props;
		props.add({property::USER_PROPERTY, NAME1, VALUE1});
		props.add({property::USER_PROPERTY, NAME2, VALUE2});

		string	name1, value1,
				name2, value2;

		std::tie(name1, value1) = get<string_pair>(props, property::USER_PROPERTY, 0);
		std::tie(name2, value2) = get<string_pair>(props, property::USER_PROPERTY, 1);

		REQUIRE(name1 == NAME1);
		REQUIRE(value1 == VALUE1);

		REQUIRE(name2 == NAME2);
		REQUIRE(value2 == VALUE2);
	}

}

