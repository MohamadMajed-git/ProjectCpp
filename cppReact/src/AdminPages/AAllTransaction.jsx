import { useEffect, useState } from "react";
import { ArrowRight, Calendar, DollarSign, Hash, User, ArrowUpRight, ArrowDownLeft } from 'lucide-react';
import axiosClient from "../axiosClient";

export default function AAllTransaction() {
    const [usersTransactions,setUsersTransactions]=useState(null);
    
    useEffect(()=>{
        axiosClient.get("/all-transactions")
        .then(res=>{
            console.log(res);
            setUsersTransactions(res.data.transactions);
        })
    },[]);
    return (
<div className="space-y-4">
    {usersTransactions && usersTransactions.length > 0 ? (
        usersTransactions.map((transaction, index) => (
            <div 
                key={index} 
                className="bg-white border border-gray-200 rounded-xl p-5 shadow-sm hover:shadow-md transition-all duration-200"
            >
                {/* الجزء العلوي: رقم المعاملة والتاريخ */}
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

                {/* الجزء الأوسط: تفاصيل التحويل (من -> إلى) */}
                <div className="flex flex-col md:flex-row items-center justify-between gap-4 mb-4">
                    
                    {/* الطرف المرسل (Sender) */}
                    <div className="flex items-center gap-3 w-full md:w-1/3">
                        <div className="p-2 bg-red-50 text-red-500 rounded-full">
                            <ArrowUpRight size={20} />
                        </div>
                        <div>
                            <p className="text-xs text-gray-400 uppercase">Sender (From)</p>
                            <div className="flex items-center gap-1 font-semibold text-gray-700 text-sm">
                                <User size={14} className="text-gray-400" />
                                {transaction.senderAccountNumber}
                            </div>
                        </div>
                    </div>

                    {/* سهم الاتجاه في المنتصف */}
                    <div className="hidden md:flex text-gray-300">
                        <ArrowRight size={24} />
                    </div>

                    {/* الطرف المستلم (Receiver) */}
                    <div className="flex items-center gap-3 w-full md:w-1/3 justify-end md:flex-row-reverse">
                        <div className="p-2 bg-green-50 text-green-500 rounded-full">
                            <ArrowDownLeft size={20} />
                        </div>
                        <div className="text-right md:text-left">
                            <p className="text-xs text-gray-400 uppercase">Receiver (To)</p>
                            <div className="flex items-center gap-1 font-semibold text-gray-700 text-sm justify-end md:justify-start">
                                <User size={14} className="text-gray-400" />
                                {transaction.receiverAccountNumber}
                            </div>
                        </div>
                    </div>
                </div>

                {/* الجزء السفلي: المبلغ الإجمالي */}
                <div className="flex justify-end items-center mt-2 pt-2 border-t border-gray-50">
                    <div className="flex items-center bg-blue-50 px-4 py-2 rounded-lg border border-blue-100">
                        <span className="text-xs text-blue-600 mr-2 uppercase font-bold tracking-wider">Amount</span>
                        <DollarSign size={16} className="text-blue-600" />
                        <span className="text-lg font-bold text-blue-700">{transaction.amount}</span>
                    </div>
                </div>
            </div>
        ))
    ) : (
        <div className="text-center py-10 text-gray-500 bg-gray-50 rounded-lg border border-dashed border-gray-300">
            No transactions found in the system.
        </div>
    )}
</div>
    );
}