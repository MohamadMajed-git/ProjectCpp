import { useNavigate } from "react-router-dom";
import { useStateContext } from "./context/ContextProvider";
import { useEffect, useState } from "react";
import axiosClient from "./axiosClient";
import {
  LayoutDashboard,
  UserCircle,
  Mail,
  CreditCard,
  Wallet,
  Hash,
  Key,
  ShieldCheck
} from 'lucide-react';
export default function Home() {
  const {user,token}=useStateContext();
  const navigate = useNavigate();
  const [userData,setUserData]=useState(0);
  useEffect(()=>{
  if(user&&user.nationalID=="123456789123"){
    navigate('/admin/admin-home')
  }
  },[])
  useEffect(()=>{
    axiosClient.post("/get-user-data",{
      "email":user.email
    }).then(req=>{
      console.log(req);
      setUserData(req.data.user);
    })
  },[])
  
  console.log(user);

  const moneyFormatter = (amount)=>{
    return new Intl.NumberFormat('en-EG', {style: 'currency', currency: 'EGP'}).format(amount);
  }

return (
    <div className="min-h-screen bg-gray-50/50 p-6 md:p-10">
      <div className="max-w-5xl mx-auto space-y-8">
        <button 
        className="px-4 py-2 bg-blue-600 text-white rounded-lg shadow hover:bg-blue-700 transition"
        onClick={() => navigate('/send-money')}>Send Money</button>
        <button 
        className="px-4 py-2 bg-blue-600 text-white rounded-lg shadow hover:bg-blue-700 transition"
        onClick={() => navigate('/user-transaction')}>View Transactions</button>
        <button 
        className="px-4 py-2 bg-blue-600 text-white rounded-lg shadow hover:bg-blue-700 transition"
        onClick={() => navigate('/loan-request')}>Request Loan</button>
        <header className="flex items-center gap-4 mb-8">
          <div className="p-3 bg-blue-600 rounded-xl shadow-sm">
            <LayoutDashboard className="w-8 h-8 text-white" />
          </div>
          <div>
            <h1 className="text-3xl font-bold text-gray-900">Dashboard Overview</h1>
            <p className="text-gray-500">Welcome back, {user.firstName}!</p>
          </div>
        </header>

        <div className="grid grid-cols-1 md:grid-cols-2 gap-6">

          <div className="bg-white rounded-2xl shadow-sm border border-gray-100 overflow-hidden hover:shadow-md transition-shadow duration-300">
            <div className="bg-gray-50 px-6 py-4 border-b border-gray-100 flex items-center gap-3">
              <UserCircle className="w-6 h-6 text-blue-500" />
              <h2 className="text-lg font-semibold text-gray-800">Personal Details</h2>
            </div>
            <div className="p-6 space-y-6">
              <div className="flex items-start gap-4">
                <ShieldCheck className="w-5 h-5 text-gray-400 mt-1" />
                <div>
                  <p className="text-sm font-medium text-gray-500">Full Name</p>
                  <p className="text-base font-semibold text-gray-900">
                    {userData.name1} {userData.name2}
                  </p>
                </div>
              </div>
              <div className="flex items-start gap-4">
                <Mail className="w-5 h-5 text-gray-400 mt-1" />
                <div>
                  <p className="text-sm font-medium text-gray-500">Email Address</p>
                  <p className="text-base font-semibold text-gray-900">{userData.email}</p>
                </div>
              </div>
              <div className="flex items-start gap-4">
                <CreditCard className="w-5 h-5 text-gray-400 mt-1" />
                <div>
                  <p className="text-sm font-medium text-gray-500">National ID</p>
                  <p className="text-base font-semibold text-gray-900 tracking-wider">{userData.nationalID}</p>
                </div>
              </div>
            </div>
          </div>

          <div className="bg-white rounded-2xl shadow-sm border border-gray-100 overflow-hidden hover:shadow-md transition-shadow duration-300 flex flex-col">
            <div className="bg-gray-50 px-6 py-4 border-b border-gray-100 flex items-center gap-3">
              <Wallet className="w-6 h-6 text-green-600" />
              <h2 className="text-lg font-semibold text-gray-800">Financial Account</h2>
            </div>
            <div className="p-6 space-y-8 flex-1 flex flex-col justify-center">
               <div className="text-center p-4 bg-green-50 rounded-xl border border-green-100">
                  <p className="text-sm font-medium text-green-600 mb-1">Current Balance</p>
                  <p className="text-4xl font-extrabold text-green-700">
                    {moneyFormatter(userData.balance)}
                  </p>
               </div>

              <div className="flex items-center gap-4 bg-gray-50 p-4 rounded-lg">
                <div className="p-2 bg-white rounded-md shadow-sm">
                    <Hash className="w-5 h-5 text-gray-600" />
                </div>
                <div>
                  <p className="text-sm font-medium text-gray-500">Account Number</p>
                  <p className="text-lg font-mono font-bold text-gray-800 tracking-widest">
                    {userData.accountNumber}
                  </p>
                </div>
              </div>
            </div>
          </div>
        </div>

        <div className="mt-8 bg-gray-100 rounded-xl p-4 border border-gray-200">
          <div className="flex items-center gap-2 mb-3">
             <Key className="w-5 h-5 text-gray-600" />
             <h3 className="text-sm font-bold text-gray-700 uppercase tracking-wider">Security Token (Debug View)</h3>
          </div>
          <div className="bg-gray-800 rounded-lg p-3 overflow-x-auto">
            <code className="text-xs text-green-400 font-mono break-all">
              {token}
            </code>
          </div>
          <p className="text-xs text-gray-500 mt-2 flex items-center gap-1">
            <ShieldCheck className="w-3 h-3" />
            Keep this token secure. Do not share it with anyone.
          </p>
        </div>

      </div>
    </div>
  );
}