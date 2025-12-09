import { useEffect, useState } from "react";
import { ArrowUpRight, ArrowDownLeft, Calendar, Hash, User } from 'lucide-react';import axiosClient from "../axiosClient";
import { useStateContext } from "../context/ContextProvider";

export default function UserTransaction() {
    const [userTransactions,setUserTransactions]=useState(null);
    const {user}=useStateContext();
    
    useEffect(()=>{
        axiosClient.post("/user-transaction",{
            "accountNumber":user.accountNumber
        })
        .then(res=>{
            console.log(res);
            setUserTransactions(res.data.transactions);
        })
    },[]);
    return (
<div className="space-y-4">
    {userTransactions && userTransactions.length > 0 ? (
        userTransactions.map((transaction, index) => {
            const isSender = transaction.senderAccountNumber === user.accountNumber;

            return (
                <div 
                    key={index} 
                    className={`bg-white border-l-4 rounded-r-xl p-5 shadow-sm hover:shadow-md transition-all duration-200 ${
                        isSender ? 'border-red-500' : 'border-green-500'
                    }`}
                >
                    <div className="flex justify-between items-center mb-4 pb-2 border-b border-gray-100">
                        <div className="flex items-center text-gray-500 text-xs font-medium">
                            <Hash size={14} className="mr-1 text-gray-400" />
                            <span>{transaction.id}</span>
                        </div>
                        <div className="flex items-center text-gray-400 text-xs">
                            <Calendar size={14} className="mr-1" />
                            <span>{transaction.date}</span>
                        </div>
                    </div>

                    <div className="flex items-center justify-between">
                        
                        <div className="flex items-center gap-4">
                            <div className={`p-3 rounded-full ${isSender ? 'bg-red-50 text-red-500' : 'bg-green-50 text-green-500'}`}>
                                {isSender ? <ArrowUpRight size={24} /> : <ArrowDownLeft size={24} />}
                            </div>

                            <div>
                                <p className={`text-xs font-bold uppercase tracking-wider mb-1 ${isSender ? 'text-red-500' : 'text-green-500'}`}>
                                    {isSender ? 'Sent To' : 'Received From'}
                                </p>
                                <div className="flex items-center gap-2 text-gray-700 font-semibold">
                                    <User size={16} className="text-gray-400" />
                                    <span>
                                        {isSender ? transaction.receiverAccountNumber : transaction.senderAccountNumber}
                                    </span>
                                </div>
                            </div>
                        </div>

                        <div className="text-right">
                            <p className={`text-xl font-bold ${isSender ? 'text-red-600' : 'text-green-600'}`}>
                                {isSender ? '-' : '+'}{transaction.amount}
                            </p>
                            <span className="text-xs text-gray-400">EGP</span>
                        </div>
                    </div>
                </div>
            );
        })
    ) : (
        <div className="text-center py-10 text-gray-500 bg-gray-50 rounded-lg border border-dashed border-gray-300">
            No transactions found.
        </div>
    )}
</div>
    );
}