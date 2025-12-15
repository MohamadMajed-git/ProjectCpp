import { useRef } from "react";
import { useStateContext } from "../context/ContextProvider";
import axiosClient from "../axiosClient";
import { Lock, KeyRound, Save, ArrowLeft, ShieldCheck } from 'lucide-react';
import { useNavigate } from "react-router-dom";

export default function ChangePassword() {
  const newPasswordRef = useRef();
  const oldPasswordRef = useRef();
  const {user}=useStateContext();
  const navigate = useNavigate();
  const handleChangePassword = () => {
    axiosClient.post("/change-password",{
      "email":user.email,
      "newPassword":newPasswordRef.current.value,
      "oldPassword":oldPasswordRef.current.value
    }).then(res=>{
      console.log(res);
    })
  };
  return (
<div className="min-h-screen bg-gray-50/50 flex items-center justify-center p-4">
      
      <div className="bg-white w-full max-w-md rounded-2xl shadow-xl border border-gray-100 overflow-hidden">
        
        <div className="bg-gradient-to-r from-blue-700 to-blue-600 p-6 text-white relative">
          <button 
            onClick={() => navigate(-1)} 
            className="absolute top-6 left-6 text-blue-100 hover:text-white hover:bg-white/20 p-1 rounded-full transition-all"
            title="Go Back"
          >
            <ArrowLeft size={24} />
          </button>
          
          <div className="flex flex-col items-center mt-2">
            <div className="bg-white/20 p-3 rounded-full mb-3 backdrop-blur-sm shadow-inner">
                <ShieldCheck size={32} className="text-white" />
            </div>
            <h1 className="text-2xl font-bold tracking-tight">Change Password</h1>
            <p className="text-blue-100 text-sm mt-1">Secure your account with a new key</p>
          </div>
        </div>

        <div className="p-8 space-y-6">
            
            <div className="space-y-2">
                <label className="text-sm font-semibold text-gray-700 ml-1">Current Password</label>
                <div className="relative group">
                    <div className="absolute inset-y-0 left-0 pl-3 flex items-center pointer-events-none">
                        <KeyRound className="h-5 w-5 text-gray-400 group-focus-within:text-blue-600 transition-colors" />
                    </div>
                    <input 
                        ref={oldPasswordRef} 
                        type="password" 
                        placeholder="Enter your old password" 
                        className="block w-full pl-10 pr-3 py-3 border border-gray-300 rounded-xl bg-gray-50 placeholder-gray-400 focus:outline-none focus:bg-white focus:ring-2 focus:ring-blue-500 focus:border-blue-500 transition-all duration-200 text-sm"
                    />
                </div>
            </div>

            <div className="space-y-2">
                <label className="text-sm font-semibold text-gray-700 ml-1">New Password</label>
                <div className="relative group">
                    <div className="absolute inset-y-0 left-0 pl-3 flex items-center pointer-events-none">
                        <Lock className="h-5 w-5 text-gray-400 group-focus-within:text-blue-600 transition-colors" />
                    </div>
                    <input 
                        ref={newPasswordRef} 
                        type="password" 
                        placeholder="Enter strong new password" 
                        className="block w-full pl-10 pr-3 py-3 border border-gray-300 rounded-xl bg-gray-50 placeholder-gray-400 focus:outline-none focus:bg-white focus:ring-2 focus:ring-blue-500 focus:border-blue-500 transition-all duration-200 text-sm"
                    />
                </div>
                <p className="text-xs text-gray-400 px-1">
                  Make sure it's at least 8 characters including a number and symbol.
                </p>
            </div>

            <button 
                className="w-full flex items-center justify-center gap-2 py-3.5 px-4 bg-blue-600 text-white font-bold rounded-xl shadow-lg shadow-blue-200 hover:bg-blue-700 hover:shadow-xl hover:-translate-y-0.5 transition-all duration-200 focus:outline-none focus:ring-2 focus:ring-offset-2 focus:ring-blue-500 mt-6"
                onClick={handleChangePassword}
            >
                <Save size={20} />
                <span>Update Password</span>
            </button>
        </div>

      </div>
    </div>
  );
}