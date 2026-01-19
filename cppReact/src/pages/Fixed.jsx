import { useEffect, useState } from "react";
import axiosClient from "../axiosClient";
import { useStateContext } from "../context/ContextProvider";
import {
  HandCoins,
  History,
  Calendar,
  DollarSign,
  FileText,
  Search,
} from "lucide-react";
import Swal from 'sweetalert2'
const PROFIT_RATES = {
  "3 months": 0.05,
  "6 months": 0.08,
  "12 months": 0.12,
};

export default function Loan() {
  const { user } = useStateContext();

  const [amount, setAmount] = useState("");
  const [duration, setDuration] = useState("3 months");

  const [loans, setLoans] = useState([]);
  const [loading, setLoading] = useState(true);

  const profitRate = PROFIT_RATES[duration];
  const profit = amount ? amount * profitRate : 0;

  const getStateText = (state) => {
    switch (state) {
      case 0: return "Finished";
      case 1: return "Approved";
      case 2: return "Pending";
      case 3: return "Denied";
      default: return "Unknown";
    }
  };

  const getStatusBadgeStyles = (statusText) => {
    const status = statusText.toLowerCase();
    if (status.includes("pending"))
      return "bg-yellow-100 text-yellow-800 border-yellow-200";
    if (status.includes("approved"))
      return "bg-green-100 text-green-800 border-green-200";
    if (status.includes("denied"))
      return "bg-red-100 text-red-800 border-red-200";
        if (status.includes("finished"))
      return "bg-blue-100 text-blue-800 border-blue-200";
    return "bg-gray-100 text-gray-800 border-gray-200";
  };

  const handleSubmit = () => {
    const numericAmount = Number(amount);

 
    if (!numericAmount || numericAmount < 1000) {
      alert("Minimum fixed deposit amount is 1000");
      return;
    }

    axiosClient
      .post("submit-fixed-request", {
        amount: numericAmount,
        profit: Number(profit.toFixed(2)),
        duration,
        email: user.email,
      })
      .then(() => {
        Swal.fire({
          icon: 'success',
          title: 'Fixed deposit request submitted successfully',
          showConfirmButton: false,
          timer: 1500
        });
        fetchHistory();

      })
      .catch((err) => {
        console.log(err);
        const errormessage = err.response?.data?.message || err.message || "Something went wrong";
        Swal.fire({
          icon: 'error',
          title: 'Error',
          text: errormessage,
        });
      });
  };

  const fetchHistory = () => {
    setLoading(true);
    axiosClient
      .post(`client/get-fixed-history`, { email: user.email })
      .then((res) => setLoans(res.data || []))
      .finally(() => setLoading(false));
  };

  useEffect(() => {
    fetchHistory();
  }, []);

  

  return (
    <div className="min-h-screen bg-gray-50/50 p-6 md:p-10 space-y-8">

      <div className="max-w-5xl mx-auto bg-white rounded-2xl border shadow-sm">
        <div className="bg-indigo-600 p-6 flex gap-3 text-white">
          <HandCoins />
          <div>
            <h1 className="text-xl font-bold">Apply Fixed Deposit</h1>
            <p className="text-indigo-100 text-sm">
              Higher duration = higher profit
            </p>
          </div>
        </div>

        <div className="p-6 space-y-6">

          <div className="grid md:grid-cols-3 gap-4 items-end">

            <div>
              <label className="text-sm font-semibold">Amount</label>
              <div className="relative">
                <DollarSign className="absolute left-3 top-3 text-gray-400" />
                <input
                  type="number"
                  value={amount}
                  onChange={(e) => setAmount(e.target.value)}
                  className="w-full pl-10 py-2.5 border rounded-xl"
                  placeholder="Minimum 1000"
                />
              </div>
            </div>

            <div>
              <label className="text-sm font-semibold">Duration</label>
              <div className="relative">
                <Calendar className="absolute left-3 top-3 text-gray-400" />
                <select
                  value={duration}
                  onChange={(e) => setDuration(e.target.value)}
                  className="w-full pl-10 py-2.5 border rounded-xl bg-white"
                >
                  <option value="3 months">3 Months</option>
                  <option value="6 months">6 Months</option>
                  <option value="12 months">12 Months</option>
                </select>
              </div>
            </div>

            <button
              onClick={handleSubmit}
              className="bg-indigo-600 text-white py-2.5 rounded-xl hover:bg-indigo-700 flex justify-center gap-2"
            >
              <FileText size={18} />
              Submit
            </button>

          </div>

          <div className="grid md:grid-cols-3 gap-4">
            <div className="bg-gray-50 p-4 rounded-xl border">
              <p className="text-sm text-gray-500">Profit Rate</p>
              <p className="text-xl font-bold text-indigo-600">
                {(profitRate * 100).toFixed(0)}%
              </p>
            </div>

            <div className="bg-gray-50 p-4 rounded-xl border">
              <p className="text-sm text-gray-500">Expected Profit</p>
              <p className="text-xl font-bold text-green-600">
                ${profit.toFixed(2)}
              </p>
            </div>

            <div className="bg-gray-50 p-4 rounded-xl border">
              <p className="text-sm text-gray-500">Total After Duration</p>
              <p className="text-xl font-bold">
                ${(Number(amount || 0) + profit).toFixed(2)}
              </p>
            </div>
          </div>

        </div>
      </div>

      <div className="max-w-5xl mx-auto">
        <h2 className="text-2xl font-bold mb-4 flex gap-2">
          <History /> My Deposits
        </h2>

        <div className="bg-white rounded-2xl border overflow-hidden">
          {loading ? (
            <p className="p-6 text-center text-gray-500">Loading...</p>
          ) : loans.length === 0 ? (
            <p className="p-6 text-center text-gray-400">
              No records found
            </p>
          ) : (
            <table className="w-full text-sm">
              <thead className="bg-gray-50">
                <tr>
                  <th className="p-4">ID</th>
                  <th className="p-4">Duration</th>
                  <th className="p-4">Amount</th>
                  <th className="p-4">Profit</th>
                  <th className="p-4">Date</th>
                  <th className="p-4">Status</th>
                </tr>
              </thead>
              <tbody>
                {loans.map((loan) => {
                  const statusText = getStateText(loan.status);
                  return (
                    <tr key={loan.id} className="border-t">
                      <td className="p-4">#{loan.id}</td>
                      <td className="p-4">{loan.duration}</td>
                      <td className="p-4 font-bold">${loan.amount}</td>
                      <td className="p-4 text-green-600 font-bold">
                        ${loan.profit}
                      </td>
                      <td className="p-4">{loan.date}</td>
                      <td className="p-4">
                        <span
                          className={`px-2 py-1 rounded-full border text-xs ${getStatusBadgeStyles(statusText)}`}
                        >
                          {statusText}
                        </span>
                      </td>
                    </tr>
                  );
                })}
              </tbody>
            </table>
          )}
        </div>
      </div>

    </div>
  );
}
