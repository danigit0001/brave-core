// Copyright (c) 2022 The Asil Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.
import * as React from 'react'
import styled, { css } from 'styled-components'

interface BoxProps {
  multiLine: boolean
  isHost: boolean
}

const Box = styled.div<BoxProps>`
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
  direction: rtl;
  text-align: left;
  margin-bottom: 11px;
  cursor: pointer;

  ${p => p.multiLine && css`
    white-space: normal;
    word-break: break-all;
    overflow: unset;
    direction: unset;
    cursor: unset;
  `}

  ${p => p.isHost && css`
    direction: unset;
    margin-bottom: 12px;
  `}

  &:last-child {
    margin-bottom: 0;
  }
`

interface UrlElementProps {
  name: string
  onExpand?: Function
  isHost: boolean
}

function UrlElement (props: UrlElementProps) {
  const [isExpanded, setExpanded] = React.useState(false)

  const handleClick = () => {
    // TODO(nullhook): Trigger if the element overflows otherwise we're recalculating positions
    if (isExpanded) return
    setExpanded(true)
    props.onExpand?.()
  }

  return (
    <Box
      onClick={handleClick}
      multiLine={isExpanded}
      isHost={props.isHost}
    >
      {props.name}
    </Box>
  )
}

export default UrlElement
