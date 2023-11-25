City ParseCity(const Json& city_json, const string& country_phone_code, const vector<Language>& languages) {
    return {
            city_json["name"s].AsString(),
            city_json["iso_code"s].AsString(),
            country_phone_code + city_json["phone_code"s].AsString(),
            languages
    };
}

Country ParseCountry(const Json& country_json) {
    Country country{
            country_json["name"s].AsString(),
            country_json["iso_code"s].AsString(),
            country_json["phone_code"s].AsString(),
            country_json["time_zone"s].AsString()
    };

    for (const auto& langJson : country_json["languages"s].AsList()) {
        country.languages.push_back(FromString<Language>(langJson.AsString()));
    }

    return country;
}

void ParseCitySubjson(vector<City>& cities, const Json& json, const string& countryPhoneCode, const vector<Language>& languages) {
    for (const auto& cityJson : json.AsList()) {
        cities.push_back(ParseCity(cityJson.AsObject(), countryPhoneCode, languages));
    }
}

void ParseCountryJson(vector<Country>& countries, vector<City>& cities, const Json& json) {
    for (const auto& countryJson : json.AsList()) {
        Country country = ParseCountry(countryJson.AsObject());
        countries.push_back(country);
        ParseCitySubjson(cities, countryJson["cities"s], country.phone_code, country.languages);
    }
}
//Я выделил логику создания объектов City и Country в отдельные функции ParseCity и ParseCountry, соответственно.
// Также, я уменьшил количество параметров в ParseCitySubjson, передав только необходимые параметры.
