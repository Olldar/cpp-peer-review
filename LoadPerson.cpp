vector<Person> LoadPersons(string_view db_name, int db_connection_timeout, bool db_allow_exceptions,
                           DBLogLevel db_log_level, int min_age, int max_age, string_view name_filter) {
    DBConnector connector(db_allow_exceptions, db_log_level);
    DBHandler db = (db_name.starts_with("tmp."s)) ? connector.ConnectTmp(db_name, db_connection_timeout)
                                                  : connector.Connect(db_name, db_connection_timeout);

    if (!db_allow_exceptions && !db.IsOK()) {
        return {};
    }

    DBQuery query = BuildQuery(min_age, max_age, name_filter);

    return LoadPersonsFromDB(db, query);
}

DBQuery BuildQuery(int min_age, int max_age, string_view name_filter) {
    ostringstream query_str;
    query_str << "from Persons "s
              << "select Name, Age "s
              << "where Age between "s << min_age << " and "s << max_age << " "s
              << "and Name like '%"s << DBHandler::Quote(name_filter) << "%'"s;
    return DBQuery(query_str.str());
}

vector<Person> LoadPersonsFromDB(DBHandler& db, const DBQuery& query) {
    vector<Person> persons;
    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back({move(name), age});
    }
    return persons;
}

//Я вынес часть кода в отдельные функции, такие как BuildQuery и LoadPersonsFromDB,
// чтобы улучшить читаемость и поддерживаемость кода.
//Использовал тернарный оператор для более компактного
// кода при выборе типа соединения с базой данных.
