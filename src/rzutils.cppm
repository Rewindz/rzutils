module;

#include "rz/rzutils.hpp"

export module rzutils;

export namespace rz {
    using ::rz::STATUS;
    using ::rz::logCB;
    using ::rz::emptyCB;
    using ::rz::EXPECTED_UPTR;
    using ::rz::EXPECTED_SPTR;
    using ::rz::EXPECTED_PTR;
    using ::rz::EXPECTED_OBJ;

    namespace fs {
        using ::rz::fs::GetHomePath;
        using ::rz::fs::GetAppConfigPath;
        using ::rz::fs::ExistsAndIsRegularFile;
        using ::rz::fs::ExistsAndIsDirectory;
        using ::rz::fs::ExistsAndIsSymlink;
    }

    namespace json {
        using ::rz::json::JsonSerializable;
        using ::rz::json::JsonDeserializable;
        using ::rz::json::JsonAble;
        using ::rz::json::LoadObjFromJsonFile_UPTR;
        using ::rz::json::LoadObjFromJsonFile_SPTR;
        using ::rz::json::LoadObjFromJsonFile_PTR;
        using ::rz::json::LoadObjectFromJsonFile_OBJ;
        using ::rz::json::LoadObjectFromJsonFile_INPLACE;
        using ::rz::json::WriteObjToJsonFile;
        using ::rz::json::Saveable;
    }
}
