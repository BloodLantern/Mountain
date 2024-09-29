#pragma once

#include "resource.hpp"
#include "embedded_resources/resource_13130013495108453755.hpp"
#include "embedded_resources/resource_17139022876316836076.hpp"
#include "embedded_resources/resource_3518102179013777611.hpp"
#include "embedded_resources/resource_9467723258334487283.hpp"
#include "embedded_resources/resource_10097982125490285052.hpp"
#include "embedded_resources/resource_10560615441756428011.hpp"
#include "embedded_resources/resource_8414638717441225796.hpp"
#include "embedded_resources/resource_16982112266611754363.hpp"
#include "embedded_resources/resource_9914516617300152348.hpp"
#include "embedded_resources/resource_7344767717205508100.hpp"
#include "embedded_resources/resource_1074902542281558043.hpp"
#include "embedded_resources/resource_5290845577426867131.hpp"
#include "embedded_resources/resource_9273770047666001763.hpp"
#include "embedded_resources/resource_8397852258098769587.hpp"
#include "embedded_resources/resource_2544377574110585068.hpp"
#include "embedded_resources/resource_5083911923489940364.hpp"
#include "embedded_resources/resource_8915932256763674668.hpp"
#include "embedded_resources/resource_2626201325449173172.hpp"

namespace {
class ResourceHolder {
private:
	std::array<Resource, 18> resources {
		Resource(resource_13130013495108453755,	resource_13130013495108453755_path),
		Resource(resource_17139022876316836076,	resource_17139022876316836076_path),
		Resource(resource_3518102179013777611,	resource_3518102179013777611_path),
		Resource(resource_9467723258334487283,	resource_9467723258334487283_path),
		Resource(resource_10097982125490285052,	resource_10097982125490285052_path),
		Resource(resource_10560615441756428011,	resource_10560615441756428011_path),
		Resource(resource_8414638717441225796,	resource_8414638717441225796_path),
		Resource(resource_16982112266611754363,	resource_16982112266611754363_path),
		Resource(resource_9914516617300152348,	resource_9914516617300152348_path),
		Resource(resource_7344767717205508100,	resource_7344767717205508100_path),
		Resource(resource_1074902542281558043,	resource_1074902542281558043_path),
		Resource(resource_5290845577426867131,	resource_5290845577426867131_path),
		Resource(resource_9273770047666001763,	resource_9273770047666001763_path),
		Resource(resource_8397852258098769587,	resource_8397852258098769587_path),
		Resource(resource_2544377574110585068,	resource_2544377574110585068_path),
		Resource(resource_5083911923489940364,	resource_5083911923489940364_path),
		Resource(resource_8915932256763674668,	resource_8915932256763674668_path),
		Resource(resource_2626201325449173172,	resource_2626201325449173172_path),
	};

public:
	auto Gather(const std::string& file) const {
		auto it = std::find_if(resources.begin(), resources.end(), [&file](const auto& lhs) {
			return lhs.GetPath() == file;
		});
		if (it == resources.end())
			throw std::runtime_error("Unable to detect resource with name " + file);
		
		return it->GetArray();
	}

	auto Gather(const char* file) const {
		return Gather(std::string(file));
	}

	auto ListFiles() const {
		std::vector<std::string> dst{};
		dst.reserve(resources.size());
		for (auto&el : resources)
			dst.push_back(el.GetPath());

		return dst;
	}

	auto FindByFilename(const std::string& file) const {
		std::vector<Resource> dst{};
		dst.reserve(resources.size());
		std::copy_if(resources.begin(), resources.end(), std::back_inserter(dst), [&file](const auto& item) {
			auto path = item.GetPath();
			auto last_forward = path.find_last_of('\\');
			auto last_inverse = path.find_last_of('/');
			
			if (last_forward != std::string::npos)
				path = path.substr(last_forward + 1);
			else if (last_inverse != std::string::npos)
				path = path.substr(last_inverse + 1);
			return path == file;
		});
		
		return dst;
	}

	auto FindByFilename(const char* file) const {
		return FindByFilename(std::string(file));
	}

	auto operator()(const std::string& file) const {
		return Gather(file);
	}

	auto operator()(const char* file) const {
		return Gather(std::string(file));
	}
};
}
