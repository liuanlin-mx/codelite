#include "GotoDeclarationRequest.h"
#include "LSP/LSPEvent.h"
#include "event_notifier.h"
#include "file_logger.h"

LSP::GotoDeclarationRequest::GotoDeclarationRequest(const wxString& filename, size_t line, size_t column,
                                                    bool for_add_missing_header)
    : m_filename(filename)
    , m_line(line)
    , m_column(column)
    , m_for_add_missing_header(for_add_missing_header)
{
    SetMethod("textDocument/declaration");
    m_params.reset(new TextDocumentPositionParams());
    m_params->As<TextDocumentPositionParams>()->SetTextDocument(TextDocumentIdentifier(filename));
    m_params->As<TextDocumentPositionParams>()->SetPosition(Position(line, column));
}

LSP::GotoDeclarationRequest::~GotoDeclarationRequest() {}

void LSP::GotoDeclarationRequest::OnResponse(const LSP::ResponseMessage& response, wxEvtHandler* owner)
{
    clDEBUG1() << "GotoDeclarationRequest::OnResponse() is called" << endl;
    JSONItem result = response.Get("result");
    if(!result.isOk()) {
        return;
    }

    std::vector<LSP::Location> locations;
    if(result.isArray()) {
        int count = result.arraySize();
        locations.reserve(count);
        for(int i = 0; i < count; ++i) {
            LSP::Location loc;
            loc.FromJSON(result.arrayItem(i));
            locations.emplace_back(loc);
        }
    } else {
        LSP::Location loc;
        loc.FromJSON(result);
        locations.push_back(loc);
    }

    if(locations.empty())
        return;
    if(m_for_add_missing_header) {
        LSPEvent definitionEvent(wxEVT_LSP_SYMBOL_DECLARATION_FOUND);
        definitionEvent.SetLocations(locations);
        EventNotifier::Get()->AddPendingEvent(definitionEvent);
    } else {
        // Fire an event with the matching location
        LSPEvent definitionEvent(wxEVT_LSP_DEFINITION);
        definitionEvent.SetLocations(locations);
        owner->AddPendingEvent(definitionEvent);
    }
}

bool LSP::GotoDeclarationRequest::IsValidAt(const wxString& filename, size_t line, size_t col) const
{
    return (m_filename == filename) && (m_line == line) && (m_column == col);
}
