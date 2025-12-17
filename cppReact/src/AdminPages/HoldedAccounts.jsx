import { useEffect, useState } from "react";
import axiosClient from "../axiosClient";
import { User, Mail, Calendar, Check, Trash2, Clock } from 'lucide-react';
import Swal from "sweetalert2";

export default function HoldedAccounts() {
  const [data,setData]=useState();
  const [reload,setReload]=useState(false);
    useEffect(()=>{
  axiosClient.get("/holded-accounts")
  .then(response=>
  {
    setData(response.data.accounts);
  }).catch(error=>
    {
      console.log(error);
    }
  );

  },[reload]);

  const handleActive=()=>{
    axiosClient.post("/holded-accounts/activate")
    .then(response=>
    {
      Swal.fire({
        icon: 'success',
        title: 'Accounts Activated Successfully',
        showConfirmButton: false,
        timer: 1500
      })
      setReload(!reload);
      console.log(response);
    })
    .catch(error=>
      {
        console.log(error);
        const errormessage = error.response.data.message|| error.message || "Something went wrong";
        Swal.fire({
          icon: 'error',
          title: 'Error',
          text: errormessage,
        })
      }
    );
  }

  const handleDelete=()=>{
    axiosClient.post("/holded-accounts/delete")
    .then(response=>
    {
      Swal.fire({
        icon: 'success',
        title: 'Accounts Deleted Successfully',
        showConfirmButton: false,
        timer: 1500
      })
      setReload(!reload);
      console.log(response);
    })
    .catch(error=>{
      console.log(error);
      const errormessage = error.response.data.message|| error.message || "Something went wrong";
      Swal.fire({
        icon: 'error',
        title: 'Error',
        text: errormessage,
      })
    })
  }

  return (
<div className="max-w-4xl mx-auto p-6 space-y-4">
      
      {/* عنوان القائمة */}
      <h2 className="text-xl font-bold text-gray-800 flex items-center gap-2 mb-6">
        <Clock className="text-blue-600" />
        قائمة انتظار الحسابات (Queue)
      </h2>

      {data && data.length > 0 ? (
        data.map((account, index) => {
          const isFirst = index === 0;

          return (
            <div 
              key={index}
              className={`
                flex flex-col md:flex-row items-center justify-between p-4 rounded-xl border transition-all duration-300
                ${isFirst 
                  ? "bg-white border-blue-500 shadow-lg border-l-4 scale-100 opacity-100" 
                  : "bg-gray-100 border-gray-200 opacity-50 grayscale hover:opacity-60"}
              `}
            >
              {/* قسم البيانات */}
              <div className="flex items-center gap-4 w-full md:w-auto">
                {/* رقم الدور */}
                <div className={`
                  w-8 h-8 rounded-full flex items-center justify-center font-bold text-sm shrink-0
                  ${isFirst ? "bg-blue-600 text-white" : "bg-gray-300 text-gray-500"}
                `}>
                  {index + 1}
                </div>

                <div className="flex flex-col">
                  <span className="font-bold text-gray-800 text-lg flex items-center gap-2">
                    <User size={18} className="text-gray-500" />
                    {account.name}
                  </span>
                  
                  <div className="flex flex-wrap gap-4 text-sm text-gray-500 mt-1">
                    <span className="flex items-center gap-1">
                      <Mail size={14} /> {account.email}
                    </span>
                    <span className="flex items-center gap-1">
                      <Calendar size={14} /> {account.creationDate}
                    </span>
                  </div>
                </div>
              </div>

              {/* قسم الأزرار */}
              <div className="flex items-center gap-3 mt-4 md:mt-0 w-full md:w-auto justify-end">
                
                {/* زر التفعيل */}
                <button 
                  disabled={!isFirst}
                  onClick={() => handleActive(account.email)} // تمرير الإيميل للدالة الخارجية
                  className={`
                    flex items-center gap-2 px-4 py-2 rounded-lg font-medium transition-all duration-200
                    ${isFirst 
                      ? "bg-green-600 text-white hover:bg-green-700 hover:shadow-md" 
                      : "bg-gray-300 text-gray-500 cursor-not-allowed"}
                  `}
                >
                  <Check size={18} />
                  <span>Activate</span>
                </button>

                {/* زر الحذف */}
                <button
                  disabled={!isFirst}
                  onClick={() => handleDelete(account.email)} // تمرير الإيميل للدالة الخارجية
                  className={`
                    flex items-center gap-2 px-4 py-2 rounded-lg font-medium transition-all duration-200
                    ${isFirst 
                      ? "bg-red-50 text-red-600 border border-red-200 hover:bg-red-100" 
                      : "bg-transparent text-gray-400 border border-gray-300 cursor-not-allowed"}
                  `}
                >
                  <Trash2 size={18} />
                  <span>Delete</span>
                </button>

              </div>
            </div>
          );
        })
      ) : (
        <div className="text-center text-gray-500 py-10">
          لا توجد حسابات معلقة حالياً.
        </div>
      )}
    </div>
  );
}