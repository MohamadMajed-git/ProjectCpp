import { useRef } from "react";
import axiosClient from "../axiosClient";
import { useStateContext } from "../context/ContextProvider";

export default function SendMoney() {
    const moneyRef=useRef(null);
    const accountRef=useRef(null);
    const {user}=useStateContext();
    const handleSend=()=>{
        const amount=moneyRef.current?.value;
        const accountNumber=accountRef.current?.value;
        axiosClient.post("/send-money",{
            "amount":amount,
            "receiverAccountNumber":accountNumber,
            "senderAccountNumber":user.accountNumber
        }).then(res=>{
            alert("Money Sent Successfully");
        })
    };
    
    return (
    <div>
        <input ref={accountRef} type="text" placeholder="Recipient Account Number" className="border p-2 rounded mb-4 w-full"/>
        <input ref={moneyRef} type="number" placeholder="Amount to Send" className="border p-2 rounded mb-4 w-full"/>
        <button className="px-4 py-2 bg-green-600 text-white rounded-lg shadow hover:bg-green-700 transition"
        onClick={handleSend}
        >
            Send Money
        </button>
    </div>
  );
}