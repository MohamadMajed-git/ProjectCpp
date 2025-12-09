import { useRef } from "react";
import axiosClient from "../axiosClient";
import { useStateContext } from "../context/ContextProvider";

export default function Loan(){
    const moneyRef=useRef(null);
    const durationRef=useRef(null);
    const {user}=useStateContext()

    const handleSubmit=()=>{
            const money=Number(moneyRef.current?.value);
            const duration=durationRef.current?.value;
        axiosClient.post("submit-loan-request",{
          "moneyOfLoan":money,
          "duration":duration,
          "email":user.email,
        }).then((res)=>{
            console.log(res.data)
        })
    }
    return (
        <div>
            <input ref={moneyRef} type="number" placeholder="enter loan"/>
            <select ref={durationRef} defaultValue="3 months">
                <option value="3 months">3 months</option>
                <option value="6 months">6 mothes</option>
                <option value="12 months">12 mothes</option>
            </select>
            <button className="bg-blue-500 border-1 hover:bg-blue-400 p-2"
            onClick={handleSubmit}
            >submit</button>
        <h1>loan user</h1>
        </div>
    );
}