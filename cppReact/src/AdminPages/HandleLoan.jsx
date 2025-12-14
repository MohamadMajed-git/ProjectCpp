import { useEffect, useState } from "react";
import axiosClient from "../axiosClient";

export default function HandleLoan() {
  const [loans, setLoans] = useState([]);
  const [loading, setLoading] = useState(true);

  const fetchLoans = () => {
    setLoading(true);
    axiosClient
      .get("admin/get-all-loans")
      .then((res) => {
        setLoans(res.data || []);
      })
      .then(() => setLoading(false));
  };

  const handleApprove = (id) => {
    axiosClient
      .post("admin/approve-loan", { id })
      .then(() => fetchLoans());
  };

  const handleDeny = (id) => {
    axiosClient
      .post("admin/deny-loan", { id })
      .then(() => fetchLoans());
  };

  useEffect(() => {
 axiosClient
      .get("admin/get-all-loans")
      .then((res) => {
        setLoans(res.data || []);
      })
      .then(() => setLoading(false));
  }, []);

  return (
    <div className="p-4">
      <h1 className="text-2xl font-bold mb-4">Loan Requests (Admin)</h1>

      {loading ? (
        <p>Loading...</p>
      ) : (
        <table className="w-full border border-gray-400">
          <thead>
            <tr className="bg-gray-200">
              <th className="border p-2">ID</th>
              <th className="border p-2">Email</th>
              <th className="border p-2">Duration</th>
              <th className="border p-2">Cost</th>
              <th className="border p-2">Date</th>
              <th className="border p-2">State</th>
              <th className="border p-2">Actions</th>
            </tr>
          </thead>
          <tbody>
            {loans.map((loan) => (
              <tr key={loan.id}>
                <td className="border p-2">{loan.id}</td>
                <td className="border p-2">{loan.email}</td>
                <td className="border p-2">{loan.duration}</td>
                <td className="border p-2">{loan.loan_cost}</td>
                <td className="border p-2">{loan.date}</td>
                <td className="border p-2">{loan.states}</td>
                <td className="border p-2 flex gap-2">
                  <button
                    className="px-3 py-1 bg-green-500 text-white rounded hover:bg-green-400"
                    onClick={() => handleApprove(loan.id)}
                  >
                    Approve
                  </button>
                  <button
                    className="px-3 py-1 bg-red-500 text-white rounded hover:bg-red-400"
                    onClick={() => handleDeny(loan.id)}
                  >
                    Deny
                  </button>
                </td>
              </tr>
            ))}
          </tbody>
        </table>
      )}
    </div>
  );
}