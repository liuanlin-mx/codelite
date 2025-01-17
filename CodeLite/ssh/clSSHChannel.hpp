#ifndef CLSSHCHANNEL_H
#define CLSSHCHANNEL_H

#if USE_SFTP

#include "clSSHChannelCommon.hpp"
#include "codelite_exports.h"
#include "ssh/cl_ssh.h"

#include <wx/msgqueue.h>

class clJoinableThread;
class WXDLLIMPEXP_CL clSSHChannel : public wxEvtHandler
{
public:
    typedef std::shared_ptr<clSSHChannel> Ptr_t;
    enum eChannelType {
        kRemoteCommand,
    };

public:
    struct Message {
        wxString buffer;
        bool raw = false;
    };

protected:
    clSSH::Ptr_t m_ssh;
    SSHChannel_t m_channel = nullptr;
    clJoinableThread* m_thread = nullptr;
    wxMessageQueue<Message> m_Queue;
    wxEvtHandler* m_owner = nullptr;
    eChannelType m_type = kRemoteCommand;
    bool m_wantStderr = false;

protected:
    wxString BuildError(const wxString& prefix) const;
    void DoWrite(const wxString& buffer, bool raw);

    void OnReadError(clCommandEvent& event);
    void OnWriteError(clCommandEvent& event);
    void OnReadOutput(clCommandEvent& event);
    void OnReadStderr(clCommandEvent& event);
    void OnChannelClosed(clCommandEvent& event);
    void OnChannelPty(clCommandEvent& event);

public:
    clSSHChannel(clSSH::Ptr_t ssh, clSSHChannel::eChannelType type, wxEvtHandler* owner, bool wantStderrEvents = false);
    virtual ~clSSHChannel();

    /**
     * @brief is the channel opened?
     */
    bool IsOpen() const { return m_channel != nullptr; }

    /**
     * @brief Open the channel
     * @throw clException
     */
    void Open();

    /**
     * @brief close the channel
     */
    void Close();

    /**
     * @brief execute remote command
     * The reply will be returned to 'sink' object in form of events
     */
    void Execute(const wxString& command);

    /**
     * @brief Send a signal to remote process
     */
    void SendSignal(wxSignal sig);

    /**
     * @brief return true if the channel is busy
     */
    bool IsBusy() const;

    /**
     * @brief detach from the remote process (this does not kill it)
     */
    void Detach();
};
#endif
#endif // CLSSHCHANNEL_H
