import { useRef, useEffect, useState } from "react";
import axiosClient from "../axiosClient";
import { useStateContext } from "../context/ContextProvider";
import { HandCoins, History, Calendar, DollarSign, FileText, Search } from 'lucide-react';

export default function Loan() {
  const moneyRef = useRef(null);
  const durationRef = useRef(null);
  const { user } = useStateContext();

  const [loans, setLoans] = useState([]);
  const [loading, setLoading] = useState(true);


  const getStateText = (state) => {
    switch (state) {
      case 0: return "Finished";
      case 1: return "Approved";
      case 2: return "Pending";
      case 3: return "Denied";
      case 4: return "Late"; 
      default: return "Unknown";
    }
  };


  const handleSubmit = () => {
    const money = Number(moneyRef.current?.value);
    const duration = durationRef.current?.value;


    if (!money || money < 1000) {
      alert("Loan amount must be at least 1000");
      return;
    }

    axiosClient
      .post("submit-loan-request", {
        moneyOfLoan: money,
        duration: duration,
        email: user.email,
      })
      .then((res) => {
        console.log(res.data);
        fetchLoanHistory();
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
     else if (status.includes('finished')) {
      return "bg-blue-100 text-blue-800 border-blue-200";
    }
      else if (status.includes('late')) {
        return "bg-purple-100 text-purple-800 border-purple-200";
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

      useEffect(() => {
    if (!user?.email) return;

    axiosClient
      .post("/adman-home-data", { email: user.email })
      .then(res => {
        setData(res.data);
        console.log(res);
      })
      .catch(err => console.error("Dashboard data error", err));
  }, [user]);

  // 🔁 Periodic loan & fixed deposit time check
useEffect(() => {
  let ran = false;

  const checkLoanAndFixedTime = () => {
    if (ran) return;
    ran = true;

    axiosClient.post("/check-loan-time").catch(console.error);
    axiosClient.post("/check-fixed-time").catch(console.error);
  };

  checkLoanAndFixedTime();
  const interval = setInterval(checkLoanAndFixedTime, 5 * 60 * 1000);
  return () => clearInterval(interval);
}, []);


  return (
    <div className="min-h-screen bg-gray-50/50 p-6 md:p-10 space-y-8">

      {}
      <div className="max-w-5xl mx-auto bg-white rounded-2xl shadow-sm border border-gray-100 overflow-hidden">
        <div className="bg-indigo-600 p-6 flex items-center gap-3 text-white">
          <div className="p-2 bg-white/20 rounded-lg">
            <HandCoins size={24} />
          </div>
          <div>
            <h1 className="text-xl font-bold">Submit a Loan Request</h1>
            <p className="text-indigo-100 text-sm">Create a new financing request</p>
          </div>
        </div>

        <div className="p-6 md:p-8">
          <div className="grid grid-cols-1 md:grid-cols-3 gap-4 items-end">

            {}
            <div className="space-y-2">
              <label className="text-sm font-semibold text-gray-700">Amount</label>
              <div className="relative">
                <div className="absolute inset-y-0 left-0 pl-3 flex items-center pointer-events-none">
                  <DollarSign className="h-5 w-5 text-gray-400" />
                </div>
                <input
                  ref={moneyRef}
                  type="number"
                  placeholder="Minimum 1000"
                  className="block w-full pl-10 pr-3 py-2.5 border border-gray-300 rounded-xl focus:ring-2 focus:ring-indigo-500 outline-none"
                />
              </div>
            </div>

            {}
            <div className="space-y-2">
              <label className="text-sm font-semibold text-gray-700">Duration</label>
              <div className="relative">
                <div className="absolute inset-y-0 left-0 pl-3 flex items-center pointer-events-none">
                  <Calendar className="h-5 w-5 text-gray-400" />
                </div>
                <select
                  ref={durationRef}
                  defaultValue="3 months"
                  className="block w-full pl-10 pr-8 py-2.5 border border-gray-300 rounded-xl focus:ring-2 focus:ring-indigo-500 outline-none bg-white"
                >
                  <option value="3 months">3 Months</option>
                  <option value="6 months">6 Months</option>
                  <option value="12 months">12 Months</option>
                </select>
              </div>
            </div>

            {}
            <button
              onClick={handleSubmit}
              className="w-full py-2.5 bg-indigo-600 hover:bg-indigo-700 text-white font-medium rounded-xl shadow-md transition-all active:scale-95 flex items-center justify-center gap-2"
            >
              <FileText size={18} />
              Submit Request
            </button>

          </div>
        </div>
      </div>

      {}
      <div className="max-w-5xl mx-auto">
        <div className="flex items-center gap-2 mb-4">
          <History className="text-gray-500" />
          <h2 className="text-2xl font-bold text-gray-800">My Loan History</h2>
        </div>

        <div className="bg-white rounded-2xl shadow-sm border border-gray-100 overflow-hidden">
          {loading ? (
            <div className="p-10 text-center text-gray-500">Loading...</div>
          ) : loans.length === 0 ? (
            <div className="p-10 text-center text-gray-400">
              <Search size={40} className="mx-auto mb-2 opacity-20" />
              No loan history found.
            </div>
          ) : (
            <div className="overflow-x-auto">
              <table className="w-full text-left">
                <thead className="bg-gray-50 text-xs uppercase text-gray-500">
                  <tr>
                    <th className="p-4">ID</th>
                    <th className="p-4">Duration</th>
                    <th className="p-4">Amount</th>
                    <th className="p-4">Date</th>
                    <th className="p-4 text-center">Status</th>
                  </tr>
                </thead>
                <tbody className="divide-y">
                  {loans.map((loan) => {
                    const statusText = getStateText(loan.states);
                    return (
                      <tr key={loan.id}>
                        <td className="p-4">#{loan.id}</td>
                        <td className="p-4">{loan.duration}</td>
                        <td className="p-4 font-bold">${loan.loan_cost}</td>
                        <td className="p-4">{loan.date}</td>
                        <td className="p-4 text-center">
                          <span className={`px-3 py-1 rounded-full text-xs border ${getStatusBadgeStyles(statusText)}`}>
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
