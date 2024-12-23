#pragma once
#include <EngineBase/Object.h>
#include <EngineBase/EnginePath.h>
#include <EngineBase/EngineString.h>

template<typename ResType>
class UEngineResources : public UObject
{
public:
	UEngineResources() {};
	~UEngineResources() {};

	UEngineResources(const UEngineResources& _Other) = delete;
	UEngineResources(UEngineResources&& _Other) noexcept = delete;
	UEngineResources& operator=(const UEngineResources& _Other) = delete;
	UEngineResources& operator=(UEngineResources&& _Other) noexcept = delete;

	static std::string ToUpperName(std::string_view _Name)
	{
		return UEngineString::ToUpper(_Name);
	}

	static std::shared_ptr<ResType> Find(std::string_view _Name)
	{
		return ResMap[_Name];
	}

	static bool Contains(std::string_view _Name)
	{
		return ResMap.contains(_Name.data());
	}

	static void Release()
	{
		ResMap.clear();
	}


	static std::shared_ptr<ResType> MakeRes(std::string_view _Name, std::string_view _Path)
	{
		std::shared_ptr<ResType> NewRes = std::make_shared<ResType>();
		NewRes->SetName(_Name);
		NewRes->Path = _Path;
		ResMap.insert({ _Name.data() , NewRes});
		return NewRes;
	}

protected:
	UEnginePath Path;

private:
	static std::map<std::string, std::shared_ptr<ResType>> ResMap;

};

template<typename ResType>
std::map<std::string, std::shared_ptr<ResType>> UEngineResources<ResType>::ResMap;


