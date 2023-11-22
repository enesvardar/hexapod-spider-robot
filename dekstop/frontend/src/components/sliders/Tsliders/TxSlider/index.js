import React, { useEffect, useRef, useState } from 'react'
import { useDispatch } from 'react-redux'
import { socket_emit } from '../../../../redux/socketio/socketSlice'

export const TxSlider = () => {

    const [value, setValue] = useState(0)
    const refVal = useRef(0);

    const dispatch = useDispatch()

    refVal.current = value;

    useEffect(() => {

        const timerFcn = (preVal) => {

            if(refVal.current != preVal){
                var change = refVal.current - preVal;
                console.log(change);
                dispatch(socket_emit("tx" + change))
            }
            
            setTimeout(timerFcn, 1000, refVal.current);
        }

        setTimeout(timerFcn, 1000 , 0);

    }, [])

    return (
        <div className="slider">
            <p id="rangeValue"> Tx {value}</p>
            <input onChange={(e) => {setValue(e.target.value)}} type="range" min={-50} max={50} value={value} />
        </div>
    )
}
