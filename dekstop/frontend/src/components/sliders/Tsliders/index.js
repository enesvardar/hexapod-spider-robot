import React from 'react'
import { TxSlider } from './TxSlider'
import { TySlider } from './TySlider'
import { TzSlider } from './TzSlider'

export const Tsliders = () => {
  return (
    <div className='tsliders'>
        <TxSlider/>
        <TySlider/>
        <TzSlider/>
    </div>
  )
}
