// Copyright (c) 2022 The Asil Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import styled from 'styled-components'

export const Box = styled.div`
  background: transparent;
  border-radius: 30px;
  max-width: 800px;
  color: white;
  font-family: ${(p) => p.theme.fontFamily.heading};
  display: flex;
  align-items: baseline;
  justify-content: center;
  flex-direction: row;

  .view-title {
    font-weight: 400;
    font-size: 40px;
  }

  .dots {
    display: flex;
    gap: 5px;
    margin-left: 5px;

    span {
      width: 8px;
      height: 8px;
      border-radius: 8px;
      background-color: white;
      opacity: 0;
    }
  }
`
