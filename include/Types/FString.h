#pragma once

#include <string>

namespace sqlite_orm_ue4
{
    inline std::string FStringToStdString(const FString &fstr)
    {
        return TCHAR_TO_UTF8(*fstr);
    }

    inline FString StdStringToFString(const std::string &stdstr)
    {
        return FString(UTF8_TO_TCHAR(stdstr.data()));
    }
}

namespace sqlite_orm
{
    template<>
    struct type_printer<FString> : public text_printer {};

    template<>
    struct statement_binder<FString>
    {
        int bind(sqlite3_stmt* stmt, int index, const FString &value)
        {
            return statement_binder<std::string>().bind(stmt, index, sqlite_orm_ue4::FStringToStdString(value));
        }
    };

    template<>
    struct field_printer<FString>
    {
        std::string operator()(const FString &t) const
        {
            return sqlite_orm_ue4::FStringToStdString(t);
        }
    };

    template<>
    struct row_extractor<FString>
    {
        FString extract(const char *row_value)
        {
            return sqlite_orm_ue4::StdStringToFString(row_value);
        }
    };
}