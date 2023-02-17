/* Copyright (c) 2021 The Asil Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_PLAYLIST_PLAYLIST_SERVICE_FACTORY_H_
#define BRAVE_BROWSER_PLAYLIST_PLAYLIST_SERVICE_FACTORY_H_

#include <memory>

#include "base/memory/singleton.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

#if BUILDFLAG(IS_ANDROID)
#include "brave/components/playlist/common/mojom/playlist.mojom.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#endif  // BUILDFLAG(IS_ANDROID)

namespace playlist {
class PlaylistService;
class MediaDetectorComponentManager;

class PlaylistServiceFactory : public BrowserContextKeyedServiceFactory {
 public:
  static bool IsPlaylistEnabled(content::BrowserContext* context);

  static PlaylistService* GetForBrowserContext(
      content::BrowserContext* context);
#if BUILDFLAG(IS_ANDROID)
  static mojo::PendingRemote<mojom::PlaylistService> GetForContext(
      content::BrowserContext* context);
#endif  // BUILDFLAG(IS_ANDROID)
  static PlaylistServiceFactory* GetInstance();

  PlaylistServiceFactory(const PlaylistServiceFactory&) = delete;
  PlaylistServiceFactory& operator=(const PlaylistServiceFactory&) = delete;

  // BrowserContextKeyedServiceFactory
  void RegisterProfilePrefs(
      user_prefs::PrefRegistrySyncable* registry) override;

 private:
  friend struct base::DefaultSingletonTraits<PlaylistServiceFactory>;

  PlaylistServiceFactory();
  ~PlaylistServiceFactory() override;

  // BrowserContextKeyedServiceFactory overrides:
  KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const override;

  void PrepareMediaDetectorComponentManager();

  // The media detector component is global extension and it's used all service
  // instances.
  std::unique_ptr<MediaDetectorComponentManager>
      media_detector_component_manager_;
};

}  // namespace playlist

#endif  // BRAVE_BROWSER_PLAYLIST_PLAYLIST_SERVICE_FACTORY_H_
