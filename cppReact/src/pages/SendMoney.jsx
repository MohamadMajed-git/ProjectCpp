import { useRef, useState } from "react";
import axiosClient from "../axiosClient";
import { useStateContext } from "../context/ContextProvider";
import { Send, Hash, DollarSign, ArrowLeft, Banknote } from 'lucide-react';
import { useNavigate } from "react-router-dom";
import Swal from 'sweetalert2'
export default function SendMoney() {
    const navigate=useNavigate();
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
            Swal.fire({
                icon: 'success',
                title: 'Money sent successfully',
                showConfirmButton: false,
                timer: 1500
            })
        }).catch(err=>{
            console.log(err);
            const errormessage = err.response.data.message|| err.message || "Something went wrong";
            Swal.fire({
                icon: 'error',
                title: 'Error',
                text: errormessage,
            })
        })
    };
    
    return (
<div className="min-h-screen bg-gray-50/50 flex items-center justify-center p-4">
      
      {/* بطاقة النموذج */}
      <div className="bg-white w-full max-w-md rounded-2xl shadow-xl border border-gray-100 overflow-hidden">
        
        {/* رأس البطاقة */}
        <div className="bg-green-600 p-6 text-white relative">
          <button 
            onClick={() => navigate(-1)} 
            className="absolute top-6 left-6 text-green-100 hover:text-white transition-colors"
          >
            <ArrowLeft size={24} />
          </button>
          <div className="flex flex-col items-center mt-2">
            <div className="bg-white/20 p-3 rounded-full mb-3 backdrop-blur-sm">
                <Send size={32} className="text-white" />
            </div>
            <h2 className="text-2xl font-bold">Send Money</h2>
            <p className="text-green-100 text-sm">Transfer funds securely</p>
          </div>
        </div>

        {/* جسم النموذج */}
        <div className="p-8 space-y-6">
            
            {/* حقل رقم الحساب */}
            <div className="space-y-2">
                <label className="text-sm font-medium text-gray-700 ml-1">Recipient Account</label>
                <div className="relative group">
                    <div className="absolute inset-y-0 left-0 pl-3 flex items-center pointer-events-none">
                        <Hash className="h-5 w-5 text-gray-400 group-focus-within:text-green-600 transition-colors" />
                    </div>
                    <input 
                        ref={accountRef} 
                        type="text" 
                        placeholder="e.g. 123456789" 
                        className="block w-full pl-10 pr-3 py-3 border border-gray-300 rounded-xl leading-5 bg-gray-50 placeholder-gray-400 focus:outline-none focus:bg-white focus:ring-2 focus:ring-green-500 focus:border-green-500 transition-all duration-200 sm:text-sm"
                    />
                </div>
            </div>

            {/* حقل المبلغ */}
            <div className="space-y-2">
                <label className="text-sm font-medium text-gray-700 ml-1">Amount</label>
                <div className="relative group">
                    <div className="absolute inset-y-0 left-0 pl-3 flex items-center pointer-events-none">
                        <DollarSign className="h-5 w-5 text-gray-400 group-focus-within:text-green-600 transition-colors" />
                    </div>
                    <input 
                        ref={moneyRef} 
                        type="number" 
                        placeholder="0.00" 
                        className="block w-full pl-10 pr-3 py-3 border border-gray-300 rounded-xl leading-5 bg-gray-50 placeholder-gray-400 focus:outline-none focus:bg-white focus:ring-2 focus:ring-green-500 focus:border-green-500 transition-all duration-200 sm:text-sm"
                    />
                    <div className="absolute inset-y-0 right-0 pr-3 flex items-center pointer-events-none">
                        <span className="text-gray-400 text-xs font-bold">USD</span>
                    </div>
                </div>
            </div>

            {/* زر الإرسال */}
            <button 
                className="w-full flex items-center justify-center gap-2 py-3.5 px-4 bg-green-600 text-white font-semibold rounded-xl shadow-lg shadow-green-200 hover:bg-green-700 hover:shadow-xl hover:-translate-y-0.5 transition-all duration-200 focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-green-500 mt-4"
                onClick={handleSend}
            >
                <Banknote size={20} />
                <span>Confirm Transfer</span>
            </button>
        </div>
        
        {/* تذييل بسيط */}
        <div className="bg-gray-50 px-6 py-4 border-t border-gray-100 text-center">
            <p className="text-xs text-gray-500">
                Secure 256-bit encrypted transaction.
            </p>
        </div>

      </div>
    </div>
  );
}