import { useRef, useEffect, useState } from "react";
import axiosClient from "../axiosClient";
import { useStateContext } from "../context/ContextProvider";
import { HandCoins, History, Calendar, DollarSign, FileText, Search, AlertCircle } from 'lucide-react';
import Swal from "sweetalert2";

export default function Loan() {
  const moneyRef = useRef(null);
  const durationRef = useRef(null);
  const { user } = useStateContext();

  const [loans, setLoans] = useState([]);
  const [loading, setLoading] = useState(true);

  // Convert state number to text
  const getStateText = (state) => {
    switch (state) {
      case 0: return "Finished";
      case 1: return "Approved";
      case 2: return "Pending";
      case 3: return "Denied";
      default: return "Unknown";
    }
  };

  // Submit loan
  const handleSubmit = () => {
    const money = Number(moneyRef.current?.value);
    const duration = durationRef.current?.value;

    axiosClient
      .post("submit-loan-request", {
        moneyOfLoan: money,
        duration: duration,
        email: user.email,
      })
      .then((res) => {
        console.log(res.data);
        Swal.fire({
          icon: 'success',
          title: 'Loan request submitted successfully',
          showConfirmButton: false,
          timer: 1500
        })
        fetchLoanHistory(); // Refresh history after submitting
      }).catch(err => {
        console.log(err);
        const errormessage = err.response.data.message || err.message || "Something went wrong";
        Swal.fire({
          icon: 'error',
          title: 'Error',
          text: errormessage,
        })
      });
  };


  const getStatusBadgeStyles = (statusText) => {
  const status = statusText.toLowerCase();
  if (status.includes('pending') || status.includes('wait')) {
    return "bg-yellow-100 text-yellow-800 border-yellow-200";
  } else if (status.includes('approv') || status.includes('accept') || status.includes('done')) {
    return "bg-green-100 text-green-800 border-green-200";
  } else if (status.includes('reject') || status.includes('denied')) {
    return "bg-red-100 text-red-800 border-red-200";
  }
  return "bg-gray-100 text-gray-800 border-gray-200";
};
  const fetchLoanHistory = () => {
    setLoading(true);
    axiosClient
      .get(`client/get-loans-history?email=${user.email}`)
      .then((res) => setLoans(res.data || []))
      .finally(() => setLoading(false));
  };

  useEffect(() => {
    fetchLoanHistory();
  }, []);

  return (
<div className="min-h-screen bg-gray-50/50 p-6 md:p-10 space-y-8">
      
      <div className="max-w-5xl mx-auto bg-white rounded-2xl shadow-sm border border-gray-100 overflow-hidden">
        <div className="bg-indigo-600 p-6 flex items-center gap-3 text-white">
           <div className="p-2 bg-white/20 rounded-lg backdrop-blur-sm">
             <HandCoins size={24} />
           </div>
           <div>
             <h1 className="text-xl font-bold">Submit a Loan Request</h1>
             <p className="text-indigo-100 text-sm">Create a new financing request</p>
           </div>
        </div>

        <div className="p-6 md:p-8">
          <div className="grid grid-cols-1 md:grid-cols-3 gap-4 items-end">
            
            {/* حقل المبلغ */}
            <div className="space-y-2">
              <label className="text-sm font-semibold text-gray-700 ml-1">Amount</label>
              <div className="relative">
                <div className="absolute inset-y-0 left-0 pl-3 flex items-center pointer-events-none">
                  <DollarSign className="h-5 w-5 text-gray-400" />
                </div>
                <input
                  ref={moneyRef}
                  type="number"
                  placeholder="Enter amount"
                  className="block w-full pl-10 pr-3 py-2.5 border border-gray-300 rounded-xl focus:ring-2 focus:ring-indigo-500 focus:border-indigo-500 transition-all outline-none"
                />
              </div>
            </div>

            <div className="space-y-2">
              <label className="text-sm font-semibold text-gray-700 ml-1">Duration</label>
              <div className="relative">
                 <div className="absolute inset-y-0 left-0 pl-3 flex items-center pointer-events-none">
                  <Calendar className="h-5 w-5 text-gray-400" />
                </div>
                <select 
                  ref={durationRef} 
                  defaultValue="3 months" 
                  className="block w-full pl-10 pr-8 py-2.5 border border-gray-300 rounded-xl focus:ring-2 focus:ring-indigo-500 focus:border-indigo-500 transition-all outline-none appearance-none bg-white cursor-pointer"
                >
                  <option value="3 months">3 Months</option>
                  <option value="6 months">6 Months</option>
                  <option value="12 months">12 Months</option>
                </select>
                <div className="absolute inset-y-0 right-0 flex items-center px-2 pointer-events-none">
                  <svg className="w-4 h-4 text-gray-400" fill="none" viewBox="0 0 24 24" stroke="currentColor"><path strokeLinecap="round" strokeLinejoin="round" strokeWidth="2" d="M19 9l-7 7-7-7" /></svg>
                </div>
              </div>
            </div>

            <button
              className="w-full py-2.5 bg-indigo-600 hover:bg-indigo-700 text-white font-medium rounded-xl shadow-md transition-all duration-200 active:scale-95 flex items-center justify-center gap-2"
              onClick={handleSubmit}
            >
              <FileText size={18} />
              Submit Request
            </button>
          </div>
        </div>
      </div>

      <div className="max-w-5xl mx-auto">
        <div className="flex items-center gap-2 mb-4 px-1">
          <History className="text-gray-500" />
          <h2 className="text-2xl font-bold text-gray-800">My Loan History</h2>
        </div>

        <div className="bg-white rounded-2xl shadow-sm border border-gray-100 overflow-hidden">
          {loading ? (
            <div className="p-10 text-center text-gray-500 flex flex-col items-center">
               <div className="animate-spin rounded-full h-8 w-8 border-b-2 border-indigo-600 mb-2"></div>
               <p>Loading records...</p>
            </div>
          ) : loans.length === 0 ? (
            <div className="p-10 text-center text-gray-400 flex flex-col items-center gap-2">
               <Search size={48} className="opacity-20" />
               <p>No loan history found.</p>
            </div>
          ) : (
            <div className="overflow-x-auto">
              <table className="w-full text-left border-collapse">
                <thead>
                  <tr className="bg-gray-50 border-b border-gray-100 text-xs uppercase tracking-wider text-gray-500 font-semibold">
                    <th className="p-4">ID</th>
                    <th className="p-4">Duration</th>
                    <th className="p-4">Amount / Cost</th>
                    <th className="p-4">Date Submitted</th>
                    <th className="p-4 text-center">Status</th>
                  </tr>
                </thead>
                <tbody className="divide-y divide-gray-100 text-sm">
                  {loans.map((loan) => {
                    const statusText = getStateText(loan.states);
                    return (
                      <tr key={loan.id} className="hover:bg-gray-50/50 transition-colors">
                        <td className="p-4 font-mono text-gray-500">#{loan.id}</td>
                        <td className="p-4 text-gray-700 font-medium">
                          <div className="flex items-center gap-1.5">
                            <Calendar size={14} className="text-gray-400"/>
                            {loan.duration}
                          </div>
                        </td>
                        <td className="p-4 font-bold text-gray-800">
                           ${loan.loan_cost}
                        </td>
                        <td className="p-4 text-gray-500">{loan.date}</td>
                        <td className="p-4 text-center">
                          <span className={`inline-flex items-center px-2.5 py-0.5 rounded-full text-xs font-medium border ${getStatusBadgeStyles(statusText)}`}>
                            {statusText}
                          </span>
                        </td>
                      </tr>
                    );
                  })}
                </tbody>
              </table>
            </div>
          )}
        </div>
      </div>

    </div>
  );
}
