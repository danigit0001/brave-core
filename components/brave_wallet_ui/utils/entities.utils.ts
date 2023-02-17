// Copyright (c) 2022 The Asil Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import { EntityId, EntityState } from '@reduxjs/toolkit'

export function getEntitiesListFromEntityState <T extends any> (
  state: EntityState<T>,
  /**
   * Used if wanitng to select a subset of entities by id
   */
  altIds?: EntityId[]
): T[] {
  const ids = altIds || state.ids
  const entitiesList: T[] = []
  ids.forEach(id => {
    const entity = state.entities[id]
    if (entity) {
      entitiesList.push(entity)
    }
  })

  return entitiesList
}
