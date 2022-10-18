/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/test/base/chrome_test_suite.h"

#define ChromeTestSuite ChromeTestSuite_ChromiumImpl
#include "src/chrome/test/base/chrome_test_suite.cc"
#undef ChromeTestSuite

#include "base/no_destructor.h"
#include "base/ranges/algorithm.h"
#include "base/strings/pattern.h"
#include "base/strings/strcat.h"
#include "base/test/scoped_feature_list.h"

class BraveChromeTestSetupHelper : public testing::EmptyTestEventListener {
 public:
  struct TestAdjustments {
    std::vector<base::StringPiece> test_patterns;

    std::vector<std::string> enable_features;
    std::vector<std::string> disable_features;
  };

  BraveChromeTestSetupHelper() = default;
  ~BraveChromeTestSetupHelper() override = default;

  // testing::EmptyTestEventListener:
  void OnTestStart(const testing::TestInfo& test_info) override {
    static const base::NoDestructor<std::vector<TestAdjustments>>
        kTestAdjustments({
            // We allow FileSystem API via brave://flags, so enable it here for
            // upstream tests.
            {
                .test_patterns =
                    {
                        "BackForwardCacheFileSystemAccessBrowserTest.*",
                        "FileSystemAccessBrowserTest.*",
                        "MojoFileSystemAccessBrowserTest.*",
                        "PersistedPermissionsFileSystemAccessBrowserTest.*",
                    },
                .enable_features = {"FileSystemAccessAPI"},
            },
        });

    const std::string& test_name =
        base::StrCat({test_info.test_suite_name(), ".", test_info.name()});
    std::vector<std::string> enable_features;
    std::vector<std::string> disable_features;

    for (const auto& test_adjustments : *kTestAdjustments) {
      if (!base::ranges::any_of(test_adjustments.test_patterns,
                                [&](const auto& pattern) {
                                  return base::MatchPattern(test_name, pattern);
                                })) {
        continue;
      }
      base::ranges::copy(test_adjustments.enable_features,
                         std::back_inserter(enable_features));
      base::ranges::copy(test_adjustments.disable_features,
                         std::back_inserter(disable_features));
    }

    if (!enable_features.empty() || !disable_features.empty()) {
      scoped_feature_list_.InitFromCommandLine(
          base::JoinString(enable_features, ","),
          base::JoinString(disable_features, ","));
    }
  }

  void OnTestEnd(const testing::TestInfo& test_info) override {
    scoped_feature_list_.Reset();
  }

 private:
  base::test::ScopedFeatureList scoped_feature_list_;
};

ChromeTestSuite::ChromeTestSuite(int argc, char** argv)
    : ChromeTestSuite_ChromiumImpl(argc, argv) {}

ChromeTestSuite::~ChromeTestSuite() = default;

void ChromeTestSuite::Initialize() {
  ChromeTestSuite_ChromiumImpl::Initialize();
  brave_chrome_test_setup_helper_ =
      std::make_unique<BraveChromeTestSetupHelper>();
  testing::TestEventListeners& listeners =
      testing::UnitTest::GetInstance()->listeners();
  listeners.Append(brave_chrome_test_setup_helper_.get());
}

void ChromeTestSuite::Shutdown() {
  testing::TestEventListeners& listeners =
      testing::UnitTest::GetInstance()->listeners();
  listeners.Release(brave_chrome_test_setup_helper_.get());
  ChromeTestSuite_ChromiumImpl::Shutdown();
}
