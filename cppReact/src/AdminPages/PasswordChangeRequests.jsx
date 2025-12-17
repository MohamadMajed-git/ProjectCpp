import { useEffect, useState } from "react";
import axiosClient from "../axiosClient";
import { useStateContext } from "../context/ContextProvider";
import { KeyRound, Mail, Check, X, ShieldAlert, Lock } from 'lucide-react';
import Swal from "sweetalert2";

export default function PasswordChangeRequests() {
    const [passwordRequest,setPasswordRequest]=useState([]);
    const [reload,setReload]=useState(false);
    const {user}=useStateContext();
    useEffect(()=>{
        axiosClient.post("password-change-requests",{"email":user.email})
        .then(res=>{
            console.log(res);
            setPasswordRequest(res.data.requests);
        })
    },[reload]);


    const handleAcceptRequest=(email,newPassword)=>{
        axiosClient.post("approve-password-change",{
            "email":user.email,
            "userEmail":email,
            "newPassword":newPassword
        })
        .then(res=>{
            console.log(res);
            Swal.fire({
                icon: 'success',
                title: 'Password Change Request Approved',
                showConfirmButton: false,
                timer: 1500
            })
            setReload(!reload);
        })
        .catch(err=>{
            console.log(err);
            const errormessage = err.response.data.message|| err.message || "Something went wrong";
            Swal.fire({
                icon: 'error',
                title: 'Error',
                text: errormessage,
            })
        });
        
    };

    const handleDenyRequest=(email,newPassword)=>{
        axiosClient.post("deny-password-change",{
            "email":user.email,
            "userEmail":email,
            "newPassword":newPassword
        })
        .then(res=>{
            console.log(res);
            Swal.fire({
                icon: 'success',
                title: 'Password Change Request Denied',
                showConfirmButton: false,
                timer: 1500
            })

            setReload(!reload);
        })
        .catch(err=>{
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
<div className="max-w-4xl mx-auto p-6 space-y-4">
      
      <h1 className="text-2xl font-bold text-gray-800 flex items-center gap-2 mb-6">
        <ShieldAlert className="text-orange-600" />
        Password Change Requests
      </h1>

      {passwordRequest.length === 0 && (
        <div className="text-center py-10 bg-gray-50 rounded-xl border border-dashed border-gray-300">
          <p className="text-gray-500 text-lg">No Password Change Requests</p>
        </div>
      )}

      {passwordRequest.length > 0 && passwordRequest.map((request, index) => {
        const isFirst = index === 0;
        
        return (
          <div 
            key={index} 
            className={`
              relative flex flex-col md:flex-row items-center justify-between p-5 rounded-xl border transition-all duration-300
              ${isFirst 
                ? "bg-white border-orange-500 shadow-md ring-1 ring-orange-100 scale-100" 
                : "bg-gray-100 border-gray-200 opacity-60 grayscale hover:opacity-70"}
            `}
          >
            <div className={`
              absolute -top-3 -left-3 w-8 h-8 rounded-full flex items-center justify-center font-bold text-sm shadow-sm
              ${isFirst ? "bg-orange-600 text-white" : "bg-gray-300 text-gray-600"}
            `}>
              {index + 1}
            </div>

            <div className="flex items-center gap-4 w-full md:w-auto mb-4 md:mb-0 pl-2">
              <div className={`p-3 rounded-full ${isFirst ? "bg-orange-50 text-orange-600" : "bg-gray-200 text-gray-500"}`}>
                <KeyRound size={24} />
              </div>

              <div className="flex flex-col gap-1">
                <div className="flex items-center gap-2 text-gray-800 font-semibold">
                  <Mail size={16} className="text-gray-400" />
                  {request.email}
                </div>
                <div className="flex items-center gap-2 text-gray-600 text-sm font-mono bg-gray-50 px-2 py-1 rounded border border-gray-100">
                  <Lock size={14} className="text-gray-400" />
                  New Pass: {request.password}
                </div>
              </div>
            </div>

            <div className="flex items-center gap-3">
              
              <button 
                className={`
                  flex items-center gap-2 px-4 py-2 rounded-lg font-medium transition-colors duration-200
                  ${isFirst 
                    ? "bg-green-600 text-white hover:bg-green-700 shadow-sm" 
                    : "bg-gray-300 text-gray-500 cursor-not-allowed"}
                `}
                onClick={() => handleAcceptRequest(request.email, request.password)}
                disabled={!isFirst}
              >
                <Check size={18} />
                <span>Accept</span>
              </button> 

              <button 
                className={`
                  flex items-center gap-2 px-4 py-2 rounded-lg font-medium transition-colors duration-200
                  ${isFirst 
                    ? "bg-white text-red-600 border border-red-200 hover:bg-red-50" 
                    : "bg-transparent text-gray-400 border border-gray-300 cursor-not-allowed"}
                `}
                onClick={() => {
                   handleDenyRequest(request.email, request.password);
                }}
                disabled={!isFirst}
              >
                <X size={18} />
                <span>Deny</span>
              </button> 
            </div>                
          </div>                
        );
      })}
    </div>
  );
}