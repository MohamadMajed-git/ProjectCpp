import { useNavigate } from "react-router-dom";
import { useStateContext } from "./context/ContextProvider";
import { useEffect, useState } from "react";
import axiosClient from "./axiosClient";
import { 
  LayoutDashboard, 
  UserCircle, 
  ShieldCheck, 
  Mail, 
  CreditCard, 
  Wallet, 
  Hash, 
  Key, 
  Send, 
  History, 
  HandCoins, 
  Lock 
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


  const quickActions = [
    { 
      label: "Send Money", 
      path: "/send-money", 
      icon: <Send size={20} />, 
      color: "bg-blue-600", 
      hover: "hover:bg-blue-700" 
    },
    { 
      label: "Transactions", 
      path: "/user-transaction", 
      icon: <History size={20} />, 
      color: "bg-indigo-600", 
      hover: "hover:bg-indigo-700" 
    },
    { 
      label: "Request Loan", 
      path: "/loan-request", 
      icon: <HandCoins size={20} />, 
      color: "bg-green-600", 
      hover: "hover:bg-green-700" 
    },
    { 
      label: "Change Password", 
      path: "/change-password", 
      icon: <Lock size={20} />, 
      color: "bg-orange-600", 
      hover: "hover:bg-orange-700" 
    },{
      label: "Request Fixed",
      path: "/fixed-request",
      icon: <HandCoins size={20} />,
      color: "bg-yellow-600",
      hover: "hover:bg-yellow-700"
    },{
      label: "Branches",
      path: "/user/branches",
      icon: <Wallet size={20} />,
      color: "bg-pink-600",
      hover: "hover:bg-pink-700"
    }
  ];


return (
<div className="min-h-screen bg-gray-50/50 p-6 md:p-10 font-sans">
      <div className="max-w-5xl mx-auto space-y-8">
        
        <header className="flex flex-col md:flex-row md:items-center justify-between gap-4 mb-8">
          <div className="flex items-center gap-4">
            <div className="p-3 bg-gradient-to-br from-blue-600 to-blue-500 rounded-xl shadow-lg shadow-blue-200">
              <LayoutDashboard className="w-8 h-8 text-white" />
            </div>
            <div>
              <h1 className="text-3xl font-bold text-gray-900 tracking-tight">Dashboard Overview <span
              className={`inline-block ml-2 px-4 py-2 text-lg font-semibold  text-green-800 bg-green-100 rounded-full ${userData.status=="active"?"":"bg-red-100 text-red-800"}`}
              >{userData.status=="active"? "Active":"Hold"} </span></h1>
              <p className="text-gray-500 mt-1">Welcome back, <span className="font-semibold text-blue-600">{user?.firstName || userData?.name1}</span>!</p>
            </div>
          </div>
        </header>

        <div className="grid grid-cols-2 md:grid-cols-4 gap-4">
          {quickActions.map((action, index) => (
            <button
              key={index}
              onClick={() => navigate(action.path)}
              className={`${action.color} ${action.hover} text-white p-4 rounded-xl shadow-md transition-all duration-300 transform hover:-translate-y-1 flex flex-col items-center justify-center gap-2 group`}
            >
              <div className="p-2 bg-white/20 rounded-full group-hover:bg-white/30 transition-colors">
                {action.icon}
              </div>
              <span className="font-medium text-sm tracking-wide">{action.label}</span>
            </button>
          ))}
        </div>

        <div className="grid grid-cols-1 md:grid-cols-2 gap-6 items-start">

          <div className="bg-white rounded-2xl shadow-sm border border-gray-100 overflow-hidden hover:shadow-md transition-shadow duration-300 h-full">
            <div className="bg-gray-50/80 px-6 py-4 border-b border-gray-100 flex items-center gap-3 backdrop-blur-sm">
              <UserCircle className="w-6 h-6 text-blue-500" />
              <h2 className="text-lg font-semibold text-gray-800">Personal Details</h2>
            </div>
            <div className="p-6 space-y-6">
              
              <div className="group flex items-start gap-4 p-2 rounded-lg hover:bg-gray-50 transition-colors">
                <div className="p-2 bg-blue-50 rounded-lg text-blue-600">
                   <ShieldCheck className="w-5 h-5" />
                </div>
                <div>
                  <p className="text-xs font-medium text-gray-400 uppercase tracking-wider">Full Name</p>
                  <p className="text-base font-bold text-gray-800">
                    {userData?.name1} {userData?.name2}
                  </p>
                </div>
              </div>

              <div className="group flex items-start gap-4 p-2 rounded-lg hover:bg-gray-50 transition-colors">
                <div className="p-2 bg-purple-50 rounded-lg text-purple-600">
                   <Mail className="w-5 h-5" />
                </div>
                <div>
                  <p className="text-xs font-medium text-gray-400 uppercase tracking-wider">Email Address</p>
                  <p className="text-base font-semibold text-gray-800">{userData?.email}</p>
                </div>
              </div>

              <div className="group flex items-start gap-4 p-2 rounded-lg hover:bg-gray-50 transition-colors">
                <div className="p-2 bg-orange-50 rounded-lg text-orange-600">
                   <CreditCard className="w-5 h-5" />
                </div>
                <div>
                  <p className="text-xs font-medium text-gray-400 uppercase tracking-wider">National ID</p>
                  <p className="text-base font-semibold text-gray-800 tracking-wider">{userData?.nationalID}</p>
                </div>
              </div>

            </div>
          </div>
          <div className="bg-white rounded-2xl shadow-sm border border-gray-100 overflow-hidden hover:shadow-md transition-shadow duration-300 h-full flex flex-col">
            <div className="bg-gray-50/80 px-6 py-4 border-b border-gray-100 flex items-center gap-3">
              <Wallet className="w-6 h-6 text-green-600" />
              <h2 className="text-lg font-semibold text-gray-800">Financial Account</h2>
            </div>
            
            <div className="p-6 space-y-8 flex-1 flex flex-col justify-center">
               <div className="relative text-center p-6 bg-gradient-to-br from-green-50 to-emerald-50 rounded-2xl border border-green-100 shadow-inner">
                  <div className="absolute top-0 right-0 p-2 opacity-10">
                    <Wallet size={64} className="text-green-600" />
                  </div>
                  <p className="text-sm font-bold text-green-600 mb-2 uppercase tracking-wide">Current Balance</p>
                  <p className="text-4xl md:text-5xl font-extrabold text-gray-800 tracking-tight">
                    {moneyFormatter(userData?.balance || 0)}
                  </p>
               </div>

              <div className="flex items-center gap-4 bg-gray-50 p-4 rounded-xl border border-gray-100">
                <div className="p-3 bg-white rounded-lg shadow-sm text-gray-700">
                    <Hash className="w-6 h-6" />
                </div>
                <div>
                  <p className="text-xs font-medium text-gray-400 uppercase tracking-wider">Account Number</p>
                  <p className="text-xl font-mono font-bold text-gray-800 tracking-widest">
                    {userData?.accountNumber}
                  </p>
                </div>
              </div>
            </div>
          </div>
        </div>
        <div className="mt-8 bg-gray-900 rounded-xl p-5 border border-gray-800 shadow-lg">
          <div className="flex items-center gap-2 mb-3">
             <Key className="w-4 h-4 text-yellow-500" />
             <h3 className="text-xs font-bold text-gray-400 uppercase tracking-widest">Security Token (Private)</h3>
          </div>
          <div className="bg-black/50 rounded-lg p-4 overflow-x-auto border border-white/10">
            <code className="text-xs text-green-400 font-mono break-all font-medium">
              {token || "No token generated"}
            </code>
          </div>
          <p className="text-xs text-gray-500 mt-3 flex items-center gap-2">
            <ShieldCheck className="w-3 h-3" />
            <span>This token allows secure API access. Never share it externally.</span>
          </p>
        </div>

      </div>
    </div>
  );
}